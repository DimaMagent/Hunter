// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HPlayerController.h"
#include "HBaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

DEFINE_LOG_CATEGORY_STATIC(ControllerLog, All, All)

void AHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInput->BindAction(AdventureModeActions.MoveAction, ETriggerEvent::Triggered, this, &AHPlayerController::Move);
		EnhancedInput->BindAction(AdventureModeActions.LookAction, ETriggerEvent::Triggered, this, &AHPlayerController::LookAround);
		EnhancedInput->BindAction(AdventureModeActions.AttackAction, ETriggerEvent::Started, this, &AHPlayerController::Attack);
		EnhancedInput->BindAction(AdventureModeActions.RunAction, ETriggerEvent::Triggered, this, &AHPlayerController::RunStart);
		EnhancedInput->BindAction(AdventureModeActions.RunAction, ETriggerEvent::Completed, this, &AHPlayerController::RunEnd);
	}
}

void AHPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CachedCharacter = Cast<AHBaseCharacter>(GetCharacter());
	PlayerCameraManager->ViewPitchMin = ViewPitchMin;
	PlayerCameraManager->ViewPitchMax = ViewPitchMax;
}

void AHPlayerController::OnPossess(APawn* PawnToPossess) {
	Super::OnPossess(PawnToPossess);
	InitializeMappingContexts();
}

void AHPlayerController::Move(const FInputActionInstance& Instance)
{
	if (!CachedCharacter) { return; }

	FVector2D MoveAroundValue = Instance.GetValue().Get<FVector2D>();
	CachedCharacter->Move(MoveAroundValue);
}

void AHPlayerController::LookAround(const FInputActionInstance& Instance)
{
	if (!CachedCharacter) { return; }

	FVector2D LookAxisValue = Instance.GetValue().Get<FVector2D>();
	CachedCharacter->LookAround(LookAxisValue);
}

void AHPlayerController::Attack(const FInputActionInstance& Instance)
{
	bool bIsTriggered = Instance.GetTriggerEvent() == ETriggerEvent::Started;
	if (!CachedCharacter && !bIsTriggered) { return; }

	CachedCharacter->Attack();
}

void AHPlayerController::RunStart(const FInputActionInstance& Instance)
{

	bool bIsTriggered = Instance.GetTriggerEvent() == ETriggerEvent::Triggered;
	if (!CachedCharacter && !bIsTriggered) { return; }

	CachedCharacter->RunStart();
}

void AHPlayerController::RunEnd(const FInputActionInstance& Instance)
{
	bool bIsTriggered = Instance.GetTriggerEvent() == ETriggerEvent::Completed;
	if (!CachedCharacter && !bIsTriggered) { return; }

	CachedCharacter->RunEnd();
}

bool AHPlayerController::ValidateInputActions() const
{
	bool bIsValidAdventureModeActions = ensureMsgf(AdventureModeActions.MoveAction, TEXT("MoveAction is not set on %s"), *GetName()) &&
		ensureMsgf(AdventureModeActions.LookAction, TEXT("LookAction is not set on %s"), *GetName()) &&
		ensureMsgf(AdventureModeActions.AttackAction, TEXT("AttackAction is not set on %s"), *GetName()) &&
		ensureMsgf(AdventureModeActions.RunAction, TEXT("RunAction is not set on %s"), *GetName());;
	return bIsValidAdventureModeActions;
}

bool AHPlayerController::ValidateMappingContexts() const
{
	return 	ensureMsgf(AdventureModeMappingContext, TEXT("GameplayMappingContext is not set on %s"), *GetName());
}

void AHPlayerController::InitializeMappingContexts() const
{
	ValidateInputActions();
	if (!ValidateMappingContexts()) { return; }

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!LocalPlayer) { return; }

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!Subsystem) { return; }

	Subsystem->AddMappingContext(AdventureModeMappingContext, 0);
}



