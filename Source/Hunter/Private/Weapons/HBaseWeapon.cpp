// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HBaseWeapon.h"

AHBaseWeapon::AHBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AHBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
void AHBaseWeapon::Attack() const {

}