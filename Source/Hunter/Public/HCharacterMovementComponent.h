// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HCharacterMovementComponent.generated.h"

UENUM(BlueprintType)
enum class ELocomotionMode : uint8
{
	WalkMode,
	RunMode
};
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

	UFUNCTION(BlueprintCallable, Category = "Movement")
	ELocomotionMode GetCurrentLocomotionMode() const { return CurrentLocomotionMode; }

	void RunStart();
	void RunEnd();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0"))
	float MaxWalkModeSpeed = 350.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0"))
	float MaxRunModeSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (ClampMin = "0", ClampMax = "1.0"))
	float RunSideThreshold = 0.8f;

	ELocomotionMode CurrentLocomotionMode = ELocomotionMode::WalkMode;
	/*¬ будущем при росте количества возможных ELocomotionMode стоит создать ассоциатвный массив*/
private:
	bool CanRun() const;

	float RunSideLimit = 0.8f;
};
