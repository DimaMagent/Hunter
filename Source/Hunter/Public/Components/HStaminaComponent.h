// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HStaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, NewStamina);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTER_API UHStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHStaminaComponent();

	FOnStaminaChanged OnStaminaChanged;

	void ChangeStamina(float Count);

	float GetStaminaPercent() const { return CurrentStamina / MaxStamina; }

	bool IsHasStamina() const { return CurrentStamina > 0; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRecovery();

	FTimerHandle StaminaRecoveryPenaltyTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina", meta = (ClampMin = "0"))
	float MaxStamina = 100.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	float CurrentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina", meta = (ClampMin = "0"))
	float StaminaRecoveryPenaltyDuration = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina", meta = (ClampMin = "0"))
	float StaminaRecoveryCount = 2.0f;

private:

	UPROPERTY()
	TObjectPtr<AHBaseCharacter> CachedCharacter;

	bool bCanStaminaRecovery = true;

	void TrySettingStaminaRecoveryPenalty();

	void StaminaRecoveryPenaltyClear();

};
