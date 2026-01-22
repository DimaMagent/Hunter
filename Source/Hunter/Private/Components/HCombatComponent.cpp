// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HCombatComponent.h"
#include "Components/HWeaponComponent.h"
#include "HBaseCharacter.h"
#include "Interfaces/HWeaponOwnerInterface.h"
#include "Types/WeaponTypes.h"
#include "Types/CombatTypes.h"

UHCombatComponent::UHCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHCombatComponent::TryAttack(EAttackIntent AttackIntent)
{
	if (!CanAttack()) { return; }

	if (!CachedWeaponComponent) { return; }

	if (IsAttackInProgress()) {
		if (bComboInputAllowed) {
			bComboInputBuffered = true;
		}
	}
	else {
		CachedWeaponComponent->BeginAttack(AttackIntent);
	}
}

void UHCombatComponent::Notify_OnAttackWindowBegin()
{
	if (!CachedWeaponComponent) { return; }

	CachedWeaponComponent->SetWeaponCollisionMode(ECollisionResponse::ECR_Overlap);
}

void UHCombatComponent::Notify_OnAttackWindowEnd()
{
	if (!CachedWeaponComponent) { return; }

	CachedWeaponComponent->SetWeaponCollisionMode(ECollisionResponse::ECR_Ignore);
}

void UHCombatComponent::Notify_OnComboWindowBegin()
{
	bComboInputAllowed = true;
	bComboInputBuffered = false;
}

void UHCombatComponent::Notify_OnComboWindowEnd()
{
	bComboInputAllowed = false;
	CachedWeaponComponent->Notify_OnComboWindowEnd(bComboInputBuffered);
}

void UHCombatComponent::Notify_OnEndCombo()
{
	CachedWeaponComponent->Notify_OnComboEnd();
}


void UHCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	CachedCharacter = Cast<AHBaseCharacter>(GetOwner());
	check(CachedCharacter);
	if (CachedCharacter->Implements<UHWeaponOwnerInterface>()) {
		CachedWeaponComponent = IHWeaponOwnerInterface::Execute_GetWeaponComponent(CachedCharacter);
	}
	ensure(CachedWeaponComponent);
}

bool UHCombatComponent::CanAttack() const
{
	/*Позже нужны условия*/
	return true;
}

bool UHCombatComponent::IsAttackInProgress() const
{
	return CachedCharacter && CachedCharacter->IsAnyAnimMontageActive();
}


