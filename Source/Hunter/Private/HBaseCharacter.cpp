// Fill out your copyright notice in the Description page of Project Settings.


#include "HBaseCharacter.h"
#include "HCharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/HHealthComponent.h"
#include "Components/HCombatComponent.h"
#include "Components/HWeaponComponent.h"
#include "Components/HStaminaComponent.h"
#include "Animations/HAnimInstanceBase.h"


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

	StaminaComponent = CreateDefaultSubobject<UHStaminaComponent>("StaminaComponent");

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

void AHBaseCharacter::Attack(EAttackIntent AttackIntent) {
	EnsureFightMode();
	CombatComponent->TryAttack(AttackIntent);
}

void AHBaseCharacter::RunStart() {
	CachedMovementComponent->RunStart();
}

void AHBaseCharacter::RunEnd() {
	CachedMovementComponent->RunEnd();
}


void AHBaseCharacter::PlayAttackAnim(UAnimMontage* AttackAnimMontage)
{ 

	if (!AttackAnimMontage) { return; }

	if (!CachedAnimInstance) { return; }

	CachedAnimInstance->Montage_Play(AttackAnimMontage);

	bIsAnimMontageActive = true;

	UE_LOG(CharacterLog, Display, TEXT("Play attack anim montage"));
}

void AHBaseCharacter::PlayComboStep(FName StepName) const
{
	if (!CachedAnimInstance) { return; }

	CachedAnimInstance->Montage_JumpToSection(StepName);

	UE_LOG(CharacterLog, Display, TEXT("Plat next combo step"));
}

void AHBaseCharacter::ChangeStamina(float Count)
{
	/*Если в будущем что-либо на уровне character будет влиять на потребление выносливости, все вычисления должны будут происходить в этом методе*/
	if (!StaminaComponent) { return; }

	StaminaComponent->ChangeStamina(Count);

	UWorld* World = GetWorld();
	if (!World) { return; }

	World->GetTimerManager().SetTimer(CharacterRecoveryTimer, this, &AHBaseCharacter::Recovery, RecoveryRate, true, RecoveryDelay);
}

void AHBaseCharacter::ReceiveDamage(float Count) {
	if (!HealthComponent) { return; }

	HealthComponent->TakeDamage(Count);
}

bool AHBaseCharacter::IsCharacterAlive() const {
	if (!HealthComponent) { return false; }

	return HealthComponent->IsHasHealth();
}

bool AHBaseCharacter::IsCharacterHasStamina() const
{
	if (!StaminaComponent) { return false; }
	return StaminaComponent->IsHasStamina();
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
	/*Здесь должны быть проверки на возможность перейти в fightmode*/
	ChangeCharacterMode(ECharacterMode::FightMode);
}

void AHBaseCharacter::UpdateLookAroundMode()
{
	/*Если потребуется, можно позже добавить проверку на возможность UpdateLookAroundMode*/
	bUseControllerRotationYaw = !GetLastMovementInputVector().IsNearlyZero();
}

void AHBaseCharacter::Caching()
{
	CachedMovementComponent = Cast<UHCharacterMovementComponent>(GetCharacterMovement());

	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	if (SkeletalMesh) {
		CachedAnimInstance = Cast<UHAnimInstanceBase>(SkeletalMesh->GetAnimInstance());
	}
}

void AHBaseCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAnimMontageActive = false;
	UE_LOG(CharacterLog, Display, TEXT("Play attack anim montage end"));
}


void AHBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	Caching();

	ensure(HealthComponent);
	ensure(StaminaComponent);
	ensure(CombatComponent);
	ensure(WeaponComponent);

	CachedAnimInstance->OnMontageBlendingOut.AddDynamic(this, &AHBaseCharacter::OnMontageEnded);

	CharacterMode = ECharacterMode::AdventureMode;
}

void AHBaseCharacter::Recovery()
{
	OnCharacterRecovery.Broadcast();
}

void AHBaseCharacter::EnsureFightMode()
{
	if (CharacterMode == ECharacterMode::FightMode) { return; }
	TryEnterFightMode();
	
}


