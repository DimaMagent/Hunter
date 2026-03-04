// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HWeaponComponent.h"
#include "Weapons/HBaseWeapon.h"
#include "HBaseCharacter.h"
#include "Types/CombatTypes.h"

DEFINE_LOG_CATEGORY_STATIC(WeaponComponentLog, All, All)

UHWeaponComponent::UHWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UHWeaponComponent::BeginAttack(EAttackIntent CurrentAttackIntent) const
{
	if (!CurrentWeapon) { return; }

	CurrentWeapon->AttackDataHandle(CurrentAttackIntent);

	UAnimMontage* AttackAnim = CurrentWeapon->GetCurrentComboAnim(CurrentAttackIntent);

	if (!AttackAnim) { return; }

	if (!CachedOwner) { return; }

	

	bool bIsPlayAttackAnimSucceeded = CachedOwner->PlayAnim(AttackAnim);

	bIsPlayAttackAnimSucceeded ? CachedOwner->ChangeStamina(-CurrentWeapon->GetCurrentStaminaCost()):  OnTryAttackInterrupt.Broadcast();
}

void UHWeaponComponent::ContinueCombo(bool IsComboInputBuffered) {
	CurrentWeapon->NextComboDataHandle(IsComboInputBuffered);

	if (!IsComboInputBuffered) { return; }

	if (!CachedOwner) { return; }

	FName CurrentStepName;
	if (!CurrentWeapon->GetCurrentStepName(CurrentStepName)) { return; }

	CachedOwner->ChangeStamina(-CurrentWeapon->GetCurrentStaminaCost());

	CachedOwner->PlayComboStep(CurrentStepName);
}

void UHWeaponComponent::BeginParrying()
{
	if (!CurrentWeapon) { return; }

	CurrentWeapon->ParryingDataHandle();

	UAnimMontage* ParryingAnim = CurrentWeapon->GetParryingMontage();
	if (!ParryingAnim) { return; }

	if (!CachedOwner) { return; }

	bool bIsPlayParryingAnimSucceeded = CachedOwner->PlayAnim(ParryingAnim);

	if (bIsPlayParryingAnimSucceeded) {
		CachedOwner->ChangeStamina(-CurrentWeapon->GetCurrentStaminaCost());
	}
	else {
		UE_LOG(WeaponComponentLog, Warning, TEXT("UHWeaponComponent::BeginParrying: Play ParryingAnim was failed"));
	}

}

void UHWeaponComponent::OnComboEnded()
{
	CurrentWeapon->OnComboEnded();
}


void UHWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	if (DefaultWeaponClass) {
		const UWorld* World = GetWorld();
		check(World);

		CurrentWeapon = GetWorld()->SpawnActor<AHBaseWeapon>(DefaultWeaponClass);

		CachedOwner = Cast<AHBaseCharacter>(GetOwner());
		check(CachedOwner);

		const auto OwnerMesh = CachedOwner->GetMesh();
		check(OwnerMesh);

		CurrentWeapon->AttachToComponent(OwnerMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket"));
		CurrentWeapon->SetOwner(GetOwner());
	}
	ensure(CurrentWeapon);

	if (CachedOwner) {
		CachedOwner->OnCharacterDead.AddDynamic(this, &UHWeaponComponent::OnCharacterDead);
	}
	
}
EMoveSet UHWeaponComponent::GetMoveSet() const {
	if (!CurrentWeapon) { return EMoveSet::Unarmed; }
	return CurrentWeapon->GetMoveSet();
}

void UHWeaponComponent::OnAttackWindowBegin()
{
	SetWeaponCollisionMode(ECollisionResponse::ECR_Overlap);
}

void UHWeaponComponent::OnAttackWindowEnd()
{
	SetWeaponCollisionMode(ECollisionResponse::ECR_Ignore);
	CurrentWeapon->OnAttackWindowEnd();
}

void UHWeaponComponent::SetWeaponCollisionMode(ECollisionResponse NewMode)
{
	CurrentWeapon->SetCollsionMode(NewMode);
}

void UHWeaponComponent::OnCharacterDead()
{
	SetWeaponCollisionMode(ECollisionResponse::ECR_Ignore);
	CurrentWeapon->OnCharacterDead();
}

