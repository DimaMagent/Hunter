// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HWeaponComponent.h"
#include "Weapons/HBaseWeapon.h"
#include "HBaseCharacter.h"

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
	if (DefaultWeaponClass) {
		const UWorld* World = GetWorld();
		check(World);

		CurrentWeapon = GetWorld()->SpawnActor<AHBaseWeapon>(DefaultWeaponClass);

		const AHBaseCharacter* Owner = Cast<AHBaseCharacter>(GetOwner());
		check(Owner);

		const auto OwnerMesh = Owner->GetMesh();
		check(OwnerMesh);

		CurrentWeapon->AttachToComponent(OwnerMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket"));
	}
	ensure(CurrentWeapon);
	
}
EMoveSet UHWeaponComponent::GetMoveSet() const {
	if (!CurrentWeapon) { return EMoveSet::Unarmed; }
	return CurrentWeapon->GetMoveSet();
}

