// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HSwordWeapon.h"
#include "Types/WeaponTypes.h"

AHSwordWeapon::AHSwordWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMoveSet = EMoveSet::Sword;
}


void AHSwordWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


