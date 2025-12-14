// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/CharacterTypes.h"
#include "HBaseCharacter.generated.h"

struct FInputActionInstance;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class HUNTER_API AHBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Mode")
	FOnCharacterModeChanged OnCharacterModeChanged;

	AHBaseCharacter(const FObjectInitializer& ObjectInitializer);

	void Move(const FInputActionInstance& Instance);
	void LookAround(const FInputActionInstance& Instance);
	void Attack(const FInputActionInstance& Instance);

protected:

	virtual void BeginPlay() override;

	void TryAttack();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mode")
	ECharacterMode CharacterMode;



private:
	void EnsureFightMode();
	void ChangeCharacterMode(ECharacterMode NewMode);
	void TryEnterFightMode();
};
