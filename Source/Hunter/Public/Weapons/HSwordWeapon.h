// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/HBaseWeapon.h"
#include "HSwordWeapon.generated.h"

/* Этот класс вообще вомжно сделать чисто блюпринтовым
*/
UCLASS()
class HUNTER_API AHSwordWeapon : public AHBaseWeapon
{
	GENERATED_BODY()
	
public:
	AHSwordWeapon();

protected:
	virtual void BeginPlay() override;

};
