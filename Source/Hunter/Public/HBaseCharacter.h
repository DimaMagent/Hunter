// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HBaseCharacter.generated.h"

struct FInputActionInstance;

UCLASS()
class HUNTER_API AHBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHBaseCharacter(const FObjectInitializer& ObjectInitializer);
	void Move(const FInputActionInstance& Instance);

protected:
	virtual void BeginPlay() override;


};
