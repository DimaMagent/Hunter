// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HBaseCharacter.generated.h"

struct FInputActionInstance;
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class HUNTER_API AHBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHBaseCharacter(const FObjectInitializer& ObjectInitializer);

	void Move(const FInputActionInstance& Instance);
	void LookAround(const FInputActionInstance& Instance);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	virtual void BeginPlay() override;


};
