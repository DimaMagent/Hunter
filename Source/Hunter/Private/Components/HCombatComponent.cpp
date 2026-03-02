// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HCombatComponent.h"
#include "Components/HWeaponComponent.h"
#include "HBaseCharacter.h"
#include "Interfaces/HWeaponOwnerInterface.h"
#include "Types/WeaponTypes.h"
#include "Types/CombatTypes.h"

DEFINE_LOG_CATEGORY_STATIC(CombatLog, All, All)

UHCombatComponent::UHCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UHCombatComponent::TryAttack(EAttackIntent AttackIntent)
{
	if (!CanAttack()) { return false; }

	OnAttackStart.Broadcast();

	if (IsAttackInProgress()) {
		if (bComboInputAllowed) {
			bComboInputBuffered = true;
		}
	}
	else {
		CachedWeaponComponent->BeginAttack(AttackIntent);
	}
	return true;
}

void UHCombatComponent::Notify_OnAttackWindowBegin()
{
	if (!CachedWeaponComponent) { return; }

	CachedWeaponComponent->OnAttackWindowBegin();
}

void UHCombatComponent::Notify_OnAttackWindowEnd()
{
	if (!CachedWeaponComponent) { return; }

	CachedWeaponComponent->OnAttackWindowEnd();
}

void UHCombatComponent::Notify_OnComboWindowBegin()
{
	bComboInputAllowed = true;
	bComboInputBuffered = false;
}

void UHCombatComponent::Notify_OnComboWindowEnd()
{
	bComboInputAllowed = false;

	if (!CanAttack()) { return; }
	CachedWeaponComponent->ContinueCombo(bComboInputBuffered);
}

void UHCombatComponent::Notify_OnAttackEnded() const
{
	OnAttackEnded.Broadcast();
}

void UHCombatComponent::Notify_OnComboEnded() const
{
	OnComboEnded();
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

	if (CachedWeaponComponent) {
		CachedWeaponComponent->OnTryAttackInterrupt.AddDynamic(this, &UHCombatComponent::HandleInterruptRequest);
	}
}

void UHCombatComponent::HandleInterruptRequest()
{
	OnComboEnded();
	OnAttackInterrupted.Broadcast();
}

void UHCombatComponent::OnComboEnded() const
{
	if (!CachedWeaponComponent) { return; }
	CachedWeaponComponent->OnComboEnded();
}

bool UHCombatComponent::CanAttack() const
{
	return IsOwnerAlive() && IsOwnerHasStamina() && CachedWeaponComponent && !CachedCharacter->HasInputRestriction(EActionRestriction::BlockAttack);
}

bool UHCombatComponent::IsAttackInProgress() const
{
	if (!CachedCharacter) { 
		UE_LOG(CombatLog, Error, TEXT("Method IsAttackInProgress: CachedCharacter is not valid"))
		return false; 
	}

	return CachedCharacter && CachedCharacter->IsAnyAnimMontageActive();
}

bool UHCombatComponent::IsOwnerAlive() const
{
	if (!CachedCharacter) { return false; }

	bool bHasAlive = CachedCharacter->IsCharacterAlive();
	if (!bHasAlive) {
		UE_LOG(CombatLog, Display, TEXT("Character is dead, attack is impossible"));
	}

	return bHasAlive;
}

bool UHCombatComponent::IsOwnerHasStamina() const
{
	if (!CachedCharacter) { return false; }

	bool bHasStamina = CachedCharacter->IsCharacterHasStamina();
	if (!bHasStamina) {
		UE_LOG(CombatLog, Display, TEXT("Not enough Stamina for attack"));
	}

	return bHasStamina;
}


