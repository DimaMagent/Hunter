// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HGameUserWidget.generated.h"

class UHHealthComponent;
class UHStaminaComponent;
/**
 * 
 */
UCLASS()
class HUNTER_API UHGameUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitWidgetPawnOwner(APawn* NewWidgetPawnOwner);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly)
	float CachedHealthPercent = 100.0f;

	UPROPERTY(BlueprintReadOnly)
	float CachedStaminaPercent = 100.0f;

	UFUNCTION()
	void UpdateCurrentHealthPercent(float NewStamina);

	UFUNCTION()
	void UpdateCurrentStaminaPercent(float NewHealth);

private:
	UPROPERTY()
	TObjectPtr<APawn> CachedWidgetPawnOwner;

	UPROPERTY()
	TObjectPtr<UHHealthComponent> CachedHealthComponent;

	UPROPERTY()
	TObjectPtr<UHStaminaComponent> CachedStaminaComponent;
	
};
