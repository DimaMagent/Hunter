// Fill out your copyright notice in the Description page of Project Settings.


#include "HBaseCharacter.h"
#include "HCharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/HHealthComponent.h"
#include "Components/HCombatComponent.h"
#include "Components/HWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(CharacterLog, All, All)

AHBaseCharacter::AHBaseCharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<UHCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UHHealthComponent>("HealthComponent");

	WeaponComponent = CreateDefaultSubobject<UHWeaponComponent>("WeaponComponent");

	CombatComponent = CreateDefaultSubobject<UHCombatComponent>("CombatComponent");

	PrimaryActorTick.bCanEverTick = false;
	
}

void AHBaseCharacter::Move(const FVector2D MoveAroundValue) {
	
	AddMovementInput(GetActorForwardVector(), MoveAroundValue.X);
	AddMovementInput(GetActorRightVector(), MoveAroundValue.Y);
}

void AHBaseCharacter::LookAround(const FVector2D LookAxisValue) {

	UpdateLookAroundMode();

	AddControllerYawInput(LookAxisValue.X);
	AddControllerPitchInput(LookAxisValue.Y);

}

void AHBaseCharacter::Attack() {
	EnsureFightMode();
	CombatComponent->TryAttack();
}

void AHBaseCharacter::RunStart() {
	CachedMovementComponent->RunStart();
}

void AHBaseCharacter::RunEnd() {
	CachedMovementComponent->RunEnd();
}

void AHBaseCharacter::PlayAttackAnim(EMoveSet CurrentMoveSet) const
{ 
	if (!AttackAnims.Contains(CurrentMoveSet)) { return; }
	UAnimMontage* AttackAnimMontage = AttackAnims[CurrentMoveSet];

	if (!AttackAnimMontage) { return; }

	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	if (!SkeletalMesh) { return; }

	UAnimInstance* AnimInstance = SkeletalMesh->GetAnimInstance();
	if (!AnimInstance) { return; }

	AnimInstance->Montage_Play(AttackAnimMontage);
}

void AHBaseCharacter::ChangeCharacterMode(ECharacterMode NewMode)
{
	if (CharacterMode == NewMode) { return; }
	CharacterMode = NewMode;
	UE_LOG(CharacterLog, Display, TEXT("Change character mode %i"), CharacterMode);
	OnCharacterModeChanged.Broadcast(CharacterMode);
}

void AHBaseCharacter::TryEnterFightMode()
{
	/*«десь должны быть проверки на возможность перейти в fightmode*/
	ChangeCharacterMode(ECharacterMode::FightMode);
}

void AHBaseCharacter::UpdateLookAroundMode()
{
	/*≈сли потребуетс€ можно позже добавить проверку на возможность UpdateLookAroundMode*/
	bUseControllerRotationYaw = !GetLastMovementInputVector().IsNearlyZero();
}

void AHBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	ensure(HealthComponent);
	ensure(CombatComponent);
	ensure(WeaponComponent);
	UE_LOG(LogTemp, Warning, TEXT("Mesh: %s"), *GetMesh()->GetName());
	UE_LOG(LogTemp, Warning, TEXT("AnimInstance: %s"), *GetNameSafe(GetMesh()->GetAnimInstance()));
	CachedMovementComponent = Cast<UHCharacterMovementComponent>(GetCharacterMovement());
	CharacterMode = ECharacterMode::AdventureMode;
}

void AHBaseCharacter::EnsureFightMode()
{
	if (CharacterMode == ECharacterMode::FightMode) { return; }
	TryEnterFightMode();
	
}


