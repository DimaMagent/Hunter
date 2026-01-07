// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HCombatComponent.h"
#include "Components/HWeaponComponent.h"
#include "HBaseCharacter.h"
#include "Interfaces/HWeaponOwnerInterface.h"
#include "Types/WeaponTypes.h"

UHCombatComponent::UHCombatComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}

void UHCombatComponent::TryAttack() const
{
	if (!CanAttack()) { return; }

	if (!CachedCharacter->Implements<UHWeaponOwnerInterface>()) { return; }

	const UHWeaponComponent* WeaponComponent = IHWeaponOwnerInterface::Execute_GetWeaponComponent(CachedCharacter);
	WeaponComponent->Attack();

	const EMoveSet MoveSet = WeaponComponent->GetMoveSet();
	CachedCharacter->PlayAttackAnim(MoveSet);
}


void UHCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	CachedCharacter = Cast<AHBaseCharacter>(GetOwner());
}


void UHCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UHCombatComponent::CanAttack() const
{
	/*Позже нужны условия*/
	return true;
}


