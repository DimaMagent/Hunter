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
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHPlayerController::Move);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHPlayerController::LookAround);
		EnhancedInput->BindAction(AttackAction, ETriggerEvent::Started, this, &AHPlayerController::Attack);
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
	if (CachedCharacter) {
		CachedCharacter->Move(Instance);
	}
}

void AHPlayerController::LookAround(const FInputActionInstance& Instance)
{
	if (CachedCharacter) {
		CachedCharacter->LookAround(Instance);
	}
}

void AHPlayerController::Attack(const FInputActionInstance& Instance)
{
	if (CachedCharacter) {
		CachedCharacter->Attack(Instance);
	}
}

bool AHPlayerController::ValidateInputActions() const
{
	bool bIsValidAdventureModeActions = ensureMsgf(MoveAction, TEXT("MoveAction is not set on %s"), *GetName()) &&
		ensureMsgf(LookAction, TEXT("LookAction is not set on %s"), *GetName()) &&
		ensureMsgf(AttackAction, TEXT("AttackAction is not set on %s"), *GetName());
	return bIsValidAdventureModeActions;
}

bool AHPlayerController::ValidateMappingContexts() const
{
	return 	ensureMsgf(GameplayMappingContext, TEXT("GameplayMappingContext is not set on %s"), *GetName());
}

void AHPlayerController::InitializeMappingContexts() const
{
	ValidateInputActions();
	if (!ValidateMappingContexts()) { return; }

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!LocalPlayer) { return; }

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!Subsystem) { return; }

	Subsystem->AddMappingContext(GameplayMappingContext, 0);
}



