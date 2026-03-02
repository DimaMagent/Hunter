// Fill out your copyright notice in the Description page of Project Settings.


#include "HBaseCharacter.h"
#include "HCharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/HHealthComponent.h"
#include "Components/HCombatComponent.h"
#include "Components/HWeaponComponent.h"
#include "Components/HStaminaComponent.h"
#include "Animations/HAnimInstanceBase.h"
#include "Components/CapsuleComponent.h"


DEFINE_LOG_CATEGORY_STATIC(CharacterLog, All, All)

AHBaseCharacter::AHBaseCharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<UHCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{

	HealthComponent = CreateDefaultSubobject<UHHealthComponent>("HealthComponent");

	WeaponComponent = CreateDefaultSubobject<UHWeaponComponent>("WeaponComponent");

	CombatComponent = CreateDefaultSubobject<UHCombatComponent>("CombatComponent");

	StaminaComponent = CreateDefaultSubobject<UHStaminaComponent>("StaminaComponent");

	PrimaryActorTick.bCanEverTick = false;
	
}

void AHBaseCharacter::Move(const FVector2D MoveAroundValue) {
	if (!IsCharacterAlive()) { return; }
	if (HasInputRestriction(EActionRestriction::BlockMove)) { return; }


	AddMovementInput(GetActorForwardVector(), MoveAroundValue.X);
	AddMovementInput(GetActorRightVector(), MoveAroundValue.Y);
}

void AHBaseCharacter::LookAround(const FVector2D LookAxisValue) {

	UpdateLookAroundMode();

	AddControllerYawInput(LookAxisValue.X);
	AddControllerPitchInput(LookAxisValue.Y);

}

bool AHBaseCharacter::Attack(EAttackIntent AttackIntent) {

	if (!IsCharacterAlive()) { return false; }

	if (!CombatComponent) { return false; }

	EnsureFightMode();

	return CombatComponent->TryAttack(AttackIntent);;
}

void AHBaseCharacter::RunStart() {
	if (!IsCharacterAlive()) { return; }

	if (HasInputRestriction(EActionRestriction::BlockMove)) { return; }

	CachedMovementComponent->RunStart();
}

void AHBaseCharacter::RunEnd() {
	if (!IsCharacterAlive()) { return; }

	CachedMovementComponent->RunEnd();
}


bool AHBaseCharacter::PlayAnim(UAnimMontage* AnimMontage)
{ 
	if (bIsAnimMontageActive) { 
		UE_LOG(CharacterLog, Warning, TEXT("Failed to play anim montage because anim montage is already playing "));
		return false;
	}

	if (!AnimMontage) { return false; }

	if (!CachedAnimInstance) { return false; }
	
	float MontageDuration =  CachedAnimInstance->Montage_Play(AnimMontage);

	if (FMath::IsNearlyEqual(MontageDuration, 0.0f)) {
		UE_LOG(CharacterLog, Warning, TEXT("Failed to play anim montage"));
		bIsAnimMontageActive = false;
		return false;
	}

	bIsAnimMontageActive = true;

	return true;
}

void AHBaseCharacter::PlayComboStep(FName StepName) const
{
	if (!CachedAnimInstance) { return; }

	CachedAnimInstance->Montage_JumpToSection(StepName);

	UE_LOG(CharacterLog, Display, TEXT("Play next combo step"));
}

void AHBaseCharacter::ChangeStamina(float Count)
{
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
	return !(CharacterMode == ECharacterMode::DeathMode);
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
	ChangeCharacterMode(ECharacterMode::FightMode);
}


void AHBaseCharacter::Caching()
{
	CachedMovementComponent = Cast<UHCharacterMovementComponent>(GetCharacterMovement());

	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	if (SkeletalMesh) {
		CachedAnimInstance = Cast<UHAnimInstanceBase>(SkeletalMesh->GetAnimInstance());
	}
}

void AHBaseCharacter::OnDeath()
{
	if (!ensure(DeathAnimationMontage)) { return; }
	if (CachedMovementComponent) {
		CachedMovementComponent->DisableMovement();
	}
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	if (CapsuleComp) {
		CapsuleComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}
	if (CachedAnimInstance) {
		CachedAnimInstance->StopAllMontages(0.1f);
		bIsAnimMontageActive = false;
	}
	SetLifeSpan(LifeSpanOnDead);
	PlayAnim(DeathAnimationMontage);

	OnCharacterDead.Broadcast();
}

void AHBaseCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAnimMontageActive = false;
	UE_LOG(CharacterLog, Display, TEXT("Play anim montage ended"));
}

void AHBaseCharacter::OnHealthChanged(float NewHealthPercent)
{
	if (FMath::IsNearlyEqual(NewHealthPercent, 0.0f)) {
		ChangeCharacterMode(ECharacterMode::DeathMode);
		OnDeath();

	}
}


void AHBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	Caching();

	ensure(HealthComponent);
	ensure(StaminaComponent);
	ensure(CombatComponent);
	ensure(WeaponComponent);

	if (CachedAnimInstance) {
		CachedAnimInstance->OnMontageBlendingOut.AddDynamic(this, &AHBaseCharacter::OnMontageEnded);
	}
	if (HealthComponent) {
		HealthComponent->OnHealthChanged.AddDynamic(this, &AHBaseCharacter::OnHealthChanged);
	}

	CharacterMode = ECharacterMode::AdventureMode;
}

void AHBaseCharacter::Recovery() const
{
	OnCharacterRecovery.Broadcast();
}

void AHBaseCharacter::EnsureFightMode()
{
	if (CharacterMode == ECharacterMode::FightMode) { return; }
	TryEnterFightMode();
	
}

bool AHBaseCharacter::HasInputRestriction(EActionRestriction Restriction) const
{
	return (ActiveRestrictions & Restriction) != EActionRestriction::None;
}

void AHBaseCharacter::UpdateLookAroundMode()
{
	bUseControllerRotationYaw = !GetLastMovementInputVector().IsNearlyZero();
}


