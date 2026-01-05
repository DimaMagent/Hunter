// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/HBaseWeapon.h"
#include "HSwordWeapon.generated.h"


UCLASS()
class HUNTER_API AHSwordWeapon : public AHBaseWeapon
{
	GENERATED_BODY()
	
public:
	AHSwordWeapon();

	virtual void Attack() const override;

protected:
	virtual void BeginPlay() override;

};
