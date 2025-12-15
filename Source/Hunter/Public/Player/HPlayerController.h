// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HPlayerController.generated.h"

class AHBaseCharacter;
class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;
/**
 * 
 */
UCLASS()
class HUNTER_API AHPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* PawnToPossess) override;

	void Move(const FInputActionInstance& Instance);

	void LookAround(const FInputActionInstance& Instance);

	void Attack(const FInputActionInstance& Instance);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> GameplayMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "View")
	float ViewPitchMin = 315.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "View")
	float ViewPitchMax = 30.0f;

private:
	UPROPERTY()
	TObjectPtr<AHBaseCharacter> CachedCharacter;

	bool ValidateInputActions() const;
	bool ValidateMappingContexts() const;

	void InitializeMappingContexts() const;
};
