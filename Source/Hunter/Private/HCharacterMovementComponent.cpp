// Fill out your copyright notice in the Description page of Project Settings.


#include "HCharacterMovementComponent.h"

float UHCharacterMovementComponent::GetLocalMoveRight() const
{
	APawn* Pawn = GetPawnOwner();
	if (!Pawn) { return 0.0f; }

	const FVector& VelocityDir = Pawn->GetVelocity();
	const FVector& RightVector = GetPawnOwner() ? GetPawnOwner()->GetActorRightVector() : FVector::ZeroVector;

	const float DotProduct = FVector::DotProduct(VelocityDir, RightVector);

	UE_LOG(LogTemp, Warning, TEXT("Move Right Value: %f"), DotProduct / GetMaxSpeed());
	return DotProduct / GetMaxSpeed();
}

float UHCharacterMovementComponent::GetLocalMoveForward() const
{
	APawn* Pawn = GetPawnOwner();
	if (!Pawn) {return 0.0f;}
	
	const FVector& VelocityDir = Pawn->GetVelocity();
	const FVector& ForwardVector = GetPawnOwner() ? GetPawnOwner()->GetActorForwardVector() : FVector::ZeroVector;

	const float DotProduct = FVector::DotProduct(VelocityDir, ForwardVector);

	UE_LOG(LogTemp, Warning, TEXT("Move Forward Value: %f"), DotProduct / GetMaxSpeed());
	return DotProduct / GetMaxSpeed();

}


