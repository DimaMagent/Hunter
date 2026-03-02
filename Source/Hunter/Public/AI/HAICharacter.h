// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HBaseCharacter.h"
#include "HAICharacter.generated.h"

class UWidgetComponent;

/**
 * 
 */
UCLASS()
class HUNTER_API AHAICharacter : public AHBaseCharacter
{
	GENERATED_BODY()

public:
	AHAICharacter(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWidgetComponent> FrontHealthBarWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWidgetComponent> BackHealthBarWidget;
};
