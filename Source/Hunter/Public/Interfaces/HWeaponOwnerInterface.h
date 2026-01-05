// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HWeaponOwnerInterface.generated.h"

class UHWeaponComponent;

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UHWeaponOwnerInterface : public UInterface
{
	GENERATED_BODY()
};


class HUNTER_API IHWeaponOwnerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UHWeaponComponent* GetWeaponComponent() const;
};
