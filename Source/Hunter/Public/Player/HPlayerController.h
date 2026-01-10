// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ObjectMacros.h"
#include "HPlayerController.generated.h"

class UInputAction;
class AHBaseCharacter;
class UInputMappingContext;
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
	TObjectPtr<UInputAction> RunAction;
};
UENUM()
enum class EInputRestriction : int32 {
	None = 0,
	BlockMove = 1 << 0,
	BlockAttack = 1 << 1,
};
ENUM_CLASS_FLAGS(EInputRestriction);

/**
 * 
 */
UCLASS()
class HUNTER_API AHPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	/*Any system that adds a restriction must remove it.
	If you want to select multiple restriction, you should use  | operation*/
	void AddRestriction(EInputRestriction Restriction) { ActiveRestrictions |= Restriction; }

	void RemoveRestriction(EInputRestriction Restriction) { ActiveRestrictions &= (~Restriction); }
protected:

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* PawnToPossess) override;

	void OnMove(const FInputActionInstance& Instance);

	void OnLookAround(const FInputActionInstance& Instance);

	void OnAttack(const FInputActionInstance& Instance);

	void OnRunStart(const FInputActionInstance& Instance);

	void OnRunEnd(const FInputActionInstance& Instance);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> AdventureModeMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	FAdventureModeAction AdventureModeActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "View")
	float ViewPitchMin = 315.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "View")
	float ViewPitchMax = 30.0f;

	EInputRestriction ActiveRestrictions;

private:
	UPROPERTY()
	TObjectPtr<AHBaseCharacter> CachedCharacter;



	bool ValidateInputActions() const;
	bool ValidateMappingContexts() const;

	void InitializeMappingContexts();

	bool HasInputRestriction(EInputRestriction Restriction) const;
};
