// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HCombatComponent.h"
#include "Components/HWeaponComponent.h"
#include "HBaseCharacter.h"
#include "Interfaces/HWeaponOwnerInterface.h"
#include "Types/WeaponTypes.h"

UHCombatComponent::UHCombatComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
	CachedCharacter = Cast<AHBaseCharacter>(GetOwner());

}

void UHCombatComponent::TryAttack() const
{
	if (!CanAttack()) { return; }

	const AActor* Owner = GetOwner();
	if (!Owner) { return; }

	if (!Owner->Implements<UHWeaponOwnerInterface>()) { return; }

	const UHWeaponComponent* WeaponComponent = IHWeaponOwnerInterface::Execute_GetWeaponComponent(Owner);
	WeaponComponent->Attack();

	const EMoveSet MoveSet = WeaponComponent->GetMoveSet();
	CachedCharacter->PlayAttackAnim(MoveSet);
}


void UHCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
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


