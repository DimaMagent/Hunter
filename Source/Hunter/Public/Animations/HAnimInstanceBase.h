// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Types/CharacterTypes.h"
#include "HAnimInstanceBase.generated.h"


/**
 * 
 */
UCLASS()
class HUNTER_API UHAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Mode", meta = (BlueprintThreadSafe))
	ECharacterMode GetCurrentCachedCharacterMode() const { return CachedCharacterMode; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mode")
	ECharacterMode CachedCharacterMode = ECharacterMode::AdventureMode;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
