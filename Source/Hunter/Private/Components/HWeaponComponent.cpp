// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HWeaponComponent.h"
#include "Weapons/HBaseWeapon.h"
#include "HBaseCharacter.h"
#include "Types/CombatTypes.h"

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

	CachedOwner->ChangeStamina(-CurrentWeapon->GetCurrentStaminaCost());

	bool bIsPlayAttackAnimSucceeded = CachedOwner->PlayAttackAnim(AttackAnim);

	if (!bIsPlayAttackAnimSucceeded) {
		OnTryAttackInterrupt.Broadcast();
	}
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
	
}
EMoveSet UHWeaponComponent::GetMoveSet() const {
	if (!CurrentWeapon) { return EMoveSet::Unarmed; }
	return CurrentWeapon->GetMoveSet();
}

void UHWeaponComponent::SetWeaponCollisionMode(ECollisionResponse NewMode)
{
	CurrentWeapon->SetCollsionMode(NewMode);
}

