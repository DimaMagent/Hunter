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
	}
}

void AHPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CachedCharacter = Cast<AHBaseCharacter>(GetCharacter());
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer()) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
			Subsystem->AddMappingContext(GameplayMappingContext, 0);
		}
	}
}

void AHPlayerController::Move(const FInputActionInstance& Instance)
{
	if (CachedCharacter) {
		CachedCharacter->Move(Instance);
	}
}

