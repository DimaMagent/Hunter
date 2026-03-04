// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HPlayerController.h"
#include "HBaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Types/CombatTypes.h"
#include "UI/HGameUserWidget.h"

DEFINE_LOG_CATEGORY_STATIC(ControllerLog, All, All)


void AHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInput->BindAction(AdventureModeActions.MoveAction, ETriggerEvent::Triggered, this, &AHPlayerController::OnMove);
		EnhancedInput->BindAction(AdventureModeActions.LookAction, ETriggerEvent::Triggered, this, &AHPlayerController::OnLookAround);
		EnhancedInput->BindAction(AdventureModeActions.AttackAction, ETriggerEvent::Started, this, &AHPlayerController::OnAttack);
		EnhancedInput->BindAction(AdventureModeActions.AlternativeAttackAction, ETriggerEvent::Started, this, &AHPlayerController::OnAlternativeAttack);
		EnhancedInput->BindAction(AdventureModeActions.RunAction, ETriggerEvent::Triggered, this, &AHPlayerController::OnRunStart);
		EnhancedInput->BindAction(AdventureModeActions.RunAction, ETriggerEvent::Completed, this, &AHPlayerController::OnRunEnd);
		EnhancedInput->BindAction(AdventureModeActions.ParryingAction, ETriggerEvent::Started, this, &AHPlayerController::OnParrying);
	}
}

void AHPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PlayerCameraManager->ViewPitchMin = ViewPitchMin;
	PlayerCameraManager->ViewPitchMax = ViewPitchMax;

	if (CachedCharacter) {
		CachedCharacter->OnCharacterDead.AddDynamic(this, &AHPlayerController::OnCharacterDead);
	}
	
	if (GameplayUserWidgetClass && CachedCharacter) {
		GameplayUserWidget = CreateWidget<UHGameUserWidget>(this, GameplayUserWidgetClass);
		GameplayUserWidget->InitWidgetPawnOwner(CachedCharacter);
		GameplayUserWidget->AddToViewport();
	}
	if (DeadUserWidgetClass) {
		OnDeadUserWidget = CreateWidget<UUserWidget>(this, DeadUserWidgetClass);
		UE_LOG(ControllerLog, Error, TEXT("AHPlayerController::OnCharacterDead: OnDeadUserWidget must be Valid now"));
	}
	else {
		UE_LOG(ControllerLog, Error, TEXT("AHPlayerController::BeginPlay: DeadUserWidgetClass is not Valid"));
	}
}

void AHPlayerController::OnPossess(APawn* PawnToPossess) {
	Super::OnPossess(PawnToPossess);
	CachedCharacter = Cast<AHBaseCharacter>(PawnToPossess);
	InitializeMappingContexts();
}

void AHPlayerController::OnMove(const FInputActionInstance& Instance)
{
	if (!CachedCharacter) { return; }

	FVector2D MoveAroundValue = Instance.GetValue().Get<FVector2D>();
	CachedCharacter->Move(MoveAroundValue);
}

void AHPlayerController::OnLookAround(const FInputActionInstance& Instance)
{
	if (!CachedCharacter) { return; }

	FVector2D LookAxisValue = Instance.GetValue().Get<FVector2D>();
	CachedCharacter->LookAround(LookAxisValue);
}

void AHPlayerController::OnAttack(const FInputActionInstance& Instance)
{
	bool bIsTriggered = Instance.GetTriggerEvent() == ETriggerEvent::Started;
	if (!CachedCharacter && !bIsTriggered) { return; }

	bool bIsAttackStart = CachedCharacter->Attack(EAttackIntent::Standart);
	if (!bIsAttackStart) {
		UE_LOG(ControllerLog, Warning, TEXT("Attack is not started"));
	}
}

void AHPlayerController::OnParrying(const FInputActionInstance& Instance)
{
	bool bIsTriggered = Instance.GetTriggerEvent() == ETriggerEvent::Started;
	if (!CachedCharacter && !bIsTriggered) { return; }

	bool bIsParryingStart = CachedCharacter->Parrying();
	if (!bIsParryingStart) {
		UE_LOG(ControllerLog, Warning, TEXT("Parrying is not started"));
	}
}

void AHPlayerController::OnAlternativeAttack(const FInputActionInstance& Instance)
{
	bool bIsTriggered = Instance.GetTriggerEvent() == ETriggerEvent::Started;
	if (!CachedCharacter && !bIsTriggered) { return; }

	bool bIsAttackStart = CachedCharacter->Attack(EAttackIntent::Alternative);
	if (!bIsAttackStart) {
		UE_LOG(ControllerLog, Warning, TEXT("Alternative attack is not started"));
	}
}

void AHPlayerController::OnRunStart(const FInputActionInstance& Instance)
{
	bool bIsTriggered = Instance.GetTriggerEvent() == ETriggerEvent::Triggered;
	if (!CachedCharacter && !bIsTriggered) { return; }

	CachedCharacter->RunStart();
}

void AHPlayerController::OnRunEnd(const FInputActionInstance& Instance)
{
	bool bIsTriggered = Instance.GetTriggerEvent() == ETriggerEvent::Completed;
	if (!CachedCharacter && !bIsTriggered) { return; }

	CachedCharacter->RunEnd();
}

void AHPlayerController::OnCharacterDead() {
	if (!OnDeadUserWidget) { UE_LOG(ControllerLog, Error, TEXT("AHPlayerController::OnCharacterDead: OnDeadUserWidget is not Valid"));  return; }

	if (GameplayUserWidget) {
		GameplayUserWidget->RemoveFromViewport();
	}

	OnDeadUserWidget->AddToViewport();
}

bool AHPlayerController::ValidateInputActions() const
{
	bool bIsValidAdventureModeActions = ensureMsgf(AdventureModeActions.MoveAction, TEXT("MoveAction is not set on %s"), *GetName()) &&
		ensureMsgf(AdventureModeActions.LookAction, TEXT("LookAction is not set on %s"), *GetName()) &&
		ensureMsgf(AdventureModeActions.AttackAction, TEXT("AttackAction is not set on %s"), *GetName()) &&
		ensureMsgf(AdventureModeActions.AlternativeAttackAction, TEXT("AlternativeAttackAction is not set on %s"), *GetName()) &&
		ensureMsgf(AdventureModeActions.RunAction, TEXT("RunAction is not set on %s"), *GetName()) &&
		ensureMsgf(AdventureModeActions.ParryingAction, TEXT("ParryingAction is not set on %s"), *GetName());
	return bIsValidAdventureModeActions;
}

bool AHPlayerController::ValidateMappingContexts() const
{
	return 	ensureMsgf(AdventureModeMappingContext, TEXT("GameplayMappingContext is not set on %s"), *GetName());
}

void AHPlayerController::InitializeMappingContexts()
{
	ValidateInputActions();
	if (!ValidateMappingContexts()) { return; }

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!LocalPlayer) { return; }

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!Subsystem) { return; }

	Subsystem->AddMappingContext(AdventureModeMappingContext, 0);
}





