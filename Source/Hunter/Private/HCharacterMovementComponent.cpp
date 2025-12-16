// Fill out your copyright notice in the Description page of Project Settings.


#include "HCharacterMovementComponent.h"

float UHCharacterMovementComponent::GetLocalMoveRight() const
{
	APawn* Pawn = GetPawnOwner();
	if (!Pawn) { return 0.0f; }

	const FVector& VelocityDir = Pawn->GetVelocity();
	const FVector& RightVector = GetPawnOwner() ? GetPawnOwner()->GetActorRightVector() : FVector::ZeroVector;

	const float DotProduct = FVector::DotProduct(VelocityDir, RightVector);

	return DotProduct / GetMaxSpeed();
}

float UHCharacterMovementComponent::GetLocalMoveForward() const
{
	APawn* Pawn = GetPawnOwner();
	if (!Pawn) {return 0.0f;}
	
	const FVector& VelocityDir = Pawn->GetVelocity();
	const FVector& ForwardVector = GetPawnOwner() ? GetPawnOwner()->GetActorForwardVector() : FVector::ZeroVector;

	const float DotProduct = FVector::DotProduct(VelocityDir, ForwardVector);

	return DotProduct / GetMaxSpeed();

}

void UHCharacterMovementComponent::RunStart()
{
	if (CurrentLocomotionMode == ELocomotionMode::RunMode) {
		if (!CanRun()) { RunEnd(); }
		return;
	}

	if (!CanRun()) { return; }

	CurrentLocomotionMode = ELocomotionMode::RunMode;
	MaxWalkSpeed = MaxRunModeSpeed;
}

void UHCharacterMovementComponent::RunEnd()
{
	CurrentLocomotionMode = ELocomotionMode::WalkMode;
	MaxWalkSpeed = MaxWalkModeSpeed;
}

void UHCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	MaxWalkSpeed = MaxWalkModeSpeed;
}

bool UHCharacterMovementComponent::CanRun() const
{
	const float MoveForward = GetLocalMoveForward();
	const float MoveRight = GetLocalMoveRight();

	bool bIsMovingForward = MoveForward >= 0.0f;
	bool bIsNotMovingSideways = FMath::Abs(GetLocalMoveRight()) < RunSideLimit;

	/*Позже необходимо добавлять условия*/
	return bIsMovingForward && bIsNotMovingSideways;
}


