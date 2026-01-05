// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HWeaponComponent.h"
#include "Weapons/HBaseWeapon.h"

UHWeaponComponent::UHWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UHWeaponComponent::Attack() const
{
	if (!CurrentWeapon) { return; }
	CurrentWeapon->Attack();
}


void UHWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	ensure(CurrentWeapon);
	
}
EMoveSet UHWeaponComponent::GetMoveSet() const {
	if (!CurrentWeapon) { return EMoveSet::Unarmed; }
	return CurrentWeapon->GetMoveSet();
}

