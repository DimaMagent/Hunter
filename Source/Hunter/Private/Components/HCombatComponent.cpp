// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HCombatComponent.h"
#include "Components/HWeaponComponent.h"
#include "HBaseCharacter.h"
#include "Interfaces/HWeaponOwnerInterface.h"
#include "Types/WeaponTypes.h"
#include "Player/HPlayerController.h"

UHCombatComponent::UHCombatComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}

void UHCombatComponent::TryAttack()
{
	if (!CanAttack()) { return; }

	if (!CachedCharacter) { return; }

	if (!CachedCharacter->Implements<UHWeaponOwnerInterface>()) { return; }

	const UHWeaponComponent* WeaponComponent = IHWeaponOwnerInterface::Execute_GetWeaponComponent(CachedCharacter);
	WeaponComponent->Attack();
	if (!ensure(WeaponComponent)) { return; }

	AHPlayerController* PlayerController = Cast<AHPlayerController>(CachedCharacter->GetController());
	if (!ensure(PlayerController)) { return; }
	
	

	const EMoveSet MoveSet = WeaponComponent->GetMoveSet();
	CachedCharacter->PlayAttackAnim(MoveSet);
}

void UHCombatComponent::OnAttackWindowBegin()
{
	if (!CachedCharacter) { return; }

	AHPlayerController* PlayerController = Cast<AHPlayerController>(CachedCharacter->GetController());
	if (!PlayerController) { return; }

	PlayerController->AddRestriction(EInputRestriction::BlockMove);
	/*должен включать overlap у оружия*/
}

void UHCombatComponent::OnAttackWindowEnd()
{
	if (!CachedCharacter) { return; }

	AHPlayerController* PlayerController = Cast<AHPlayerController>(CachedCharacter->GetController());
	if (!PlayerController) { return; }

	PlayerController->RemoveRestriction(EInputRestriction::BlockMove);
	/*должен отключать overlap у оружия*/
}


void UHCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	CachedCharacter = Cast<AHBaseCharacter>(GetOwner());
	ensure(CachedCharacter);
}

bool UHCombatComponent::CanAttack() const
{
	/*Позже нужны условия*/
	if (!CachedCharacter) { return false; }
	return !CachedCharacter->IsAnyAnimMontageActive();
}


