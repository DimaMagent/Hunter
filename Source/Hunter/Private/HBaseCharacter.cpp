// Fill out your copyright notice in the Description page of Project Settings.


#include "HBaseCharacter.h"
#include "HCharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(CharacterLog, All, All)

AHBaseCharacter::AHBaseCharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<UHCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	PrimaryActorTick.bCanEverTick = false;
	
}

void AHBaseCharacter::Move(const FInputActionInstance& Instance) {
	FVector2D MoveAroundValue = Instance.GetValue().Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MoveAroundValue.X);
	AddMovementInput(GetActorRightVector(), MoveAroundValue.Y);
}

void AHBaseCharacter::LookAround(const FInputActionInstance& Instance) {
	FVector2D LookAxisValue = Instance.GetValue().Get<FVector2D>();
	AddControllerPitchInput(LookAxisValue.Y);
	AddControllerYawInput(LookAxisValue.X);
}

void AHBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


