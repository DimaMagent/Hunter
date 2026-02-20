// Fill out your copyright notice in the Description page of Project Settings.


#include "HCharacterMovementComponent.h"
#include "HBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(MovementLog, All, All)

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

void UHCharacterMovementComponent::DisableMovement()
{
	RunEnd();

	PreviousMovementMode = MovementMode;

	Super::DisableMovement();
}

void UHCharacterMovementComponent::EnableMovement()
{
	MovementMode = PreviousMovementMode;
}

void UHCharacterMovementComponent::RunStart()
{
	if (CurrentLocomotionMode == ELocomotionMode::RunMode) { return; }

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
	CachedCharacter = GetOwner<AHBaseCharacter>();
	ensure(CachedCharacter);

}

void UHCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentLocomotionMode == ELocomotionMode::RunMode && MovementMode == EMovementMode::MOVE_Walking) {

		if (!CanRun()) { RunEnd(); }

		if (CachedCharacter) {
			CachedCharacter->ChangeStamina(-RunCostPerSecond * DeltaTime);
		}
	}
}

bool UHCharacterMovementComponent::CanRun() const
{
	const float MoveForward = GetLocalMoveForward();
	const float MoveRight = GetLocalMoveRight();

	bool bIsMovingForward = MoveForward >= 0.0f;
	bool bIsNotMovingSideways = FMath::Abs(GetLocalMoveRight()) < RunSideLimit;

	return bIsMovingForward && bIsNotMovingSideways && IsOwnerHasStamina();
}

bool UHCharacterMovementComponent::IsOwnerHasStamina() const {
	if (!CachedCharacter) { return false; }
	bool bHasStamina = CachedCharacter->IsCharacterHasStamina();
	if (!bHasStamina) {
		UE_LOG(MovementLog, Display, TEXT("Not enough Stamina for run action"));
	}

	return bHasStamina;
}


