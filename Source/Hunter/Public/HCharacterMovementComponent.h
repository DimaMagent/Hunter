// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetLocalMoveRight() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetLocalMoveForward() const;

};
