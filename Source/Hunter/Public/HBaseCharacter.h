// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/CharacterTypes.h"
#include "HBaseCharacter.generated.h"

struct FInputActionInstance;
class USpringArmComponent;
class UCameraComponent;
class UHCharacterMovementComponent;
class UHHealthComponent;

UCLASS()
class HUNTER_API AHBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Mode")
	FOnCharacterModeChanged OnCharacterModeChanged;

	AHBaseCharacter(const FObjectInitializer& ObjectInitializer);

	void Move(const FVector2D MoveAroundValue);
	void LookAround(const FVector2D LookAxisValue);
	void Attack();
	void RunStart();
	void RunEnd();

	ECharacterMode GetCurrentCharacterMode() const { return CharacterMode; };

protected:

	virtual void BeginPlay() override;

	void TryAttack();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UHHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mode")
	ECharacterMode CharacterMode;



private:

	UPROPERTY()
	TObjectPtr<UHCharacterMovementComponent> CachedMovementComponent;

	void EnsureFightMode();
	void ChangeCharacterMode(ECharacterMode NewMode);
	void TryEnterFightMode();
	void UpdateLookAroundMode();
};
