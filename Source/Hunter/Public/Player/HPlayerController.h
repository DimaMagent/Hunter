// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ObjectMacros.h"
#include "HPlayerController.generated.h"

class UInputAction;
class AHBaseCharacter;
class UInputMappingContext;
class UHGameUserWidget;
struct FInputActionInstance;

USTRUCT(BlueprintType)
struct FAdventureModeAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> AlternativeAttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> ParryingAction;
};



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

	void OnMove(const FInputActionInstance& Instance);

	void OnLookAround(const FInputActionInstance& Instance);

	void OnAttack(const FInputActionInstance& Instance);

	void OnParrying(const FInputActionInstance& Instance);

	void OnAlternativeAttack(const FInputActionInstance& Instance);

	void OnRunStart(const FInputActionInstance& Instance);

	void OnRunEnd(const FInputActionInstance& Instance);

	UFUNCTION()
	virtual void OnCharacterDead();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> AdventureModeMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	FAdventureModeAction AdventureModeActions;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHGameUserWidget> GameplayUserWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> DeadUserWidgetClass;

	UPROPERTY()
	TObjectPtr<UHGameUserWidget> GameplayUserWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> OnDeadUserWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "View")
	float ViewPitchMin = 315.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "View")
	float ViewPitchMax = 30.0f;

private:

	UPROPERTY()
	TObjectPtr<AHBaseCharacter> CachedCharacter;

	bool ValidateInputActions() const;
	bool ValidateMappingContexts() const;

	void InitializeMappingContexts();


};
