// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HMainMenuWidget.generated.h"

class UButton;
class UUHUIMessageSubsystem;



/**
 * 
 */
UCLASS()
class HUNTER_API UHMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> StartButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

	UFUNCTION()
	void StartButtonClicked();

	UFUNCTION()
	void ExitButtonClicked();

private:
	UUHUIMessageSubsystem* GetUIMessageSubsystem();

	
};
