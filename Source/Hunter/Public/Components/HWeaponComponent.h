// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/WeaponTypes.h"
#include "HWeaponComponent.generated.h"

class AHBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTER_API UHWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHWeaponComponent();

	void Attack() const;
	EMoveSet GetMoveSet() const;

protected:
	virtual void BeginPlay() override;

	/*Тут надо, чтобы он принимал блюприт версию baseWeapon*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AHBaseWeapon> DefaultWeaponClass;

	UPROPERTY()
	TObjectPtr<AHBaseWeapon> CurrentWeapon;
		
};
