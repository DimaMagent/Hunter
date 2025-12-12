// Fill out your copyright notice in the Description page of Project Settings.


#include "HBaseCharacter.h"
#include "HCharacterMovementComponent.h"
#include "EnhancedInputComponent.h"

DEFINE_LOG_CATEGORY_STATIC(CharacterLog, All, All)

AHBaseCharacter::AHBaseCharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<UHCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AHBaseCharacter::Move(const FInputActionInstance& Instance) {
	FVector2D Value = Instance.GetValue().Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), Value.X);
	AddMovementInput(GetActorRightVector(), Value.Y);
}

void AHBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


