// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/WeaponTypes.h"
#include "HBaseWeapon.generated.h"


UCLASS()
class HUNTER_API AHBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AHBaseWeapon();

	virtual EMoveSet GetMoveSet() const { return WeaponMoveSet; }

	virtual void Attack() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	EMoveSet WeaponMoveSet = EMoveSet::Unarmed;

	/*Я ещё пока не решил, какая будет архитектура у атак оружием, но они должны как-то влиять на анимации, хотя у меня пока нет анимаций*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	FAttackInfo AtatackInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
};
