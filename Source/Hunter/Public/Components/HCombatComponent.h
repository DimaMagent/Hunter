// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HCombatComponent.generated.h"

class AHBaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTER_API UHCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHCombatComponent();
	void TryAttack() const;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY()
	TObjectPtr<AHBaseCharacter> CachedCharacter;

	bool CanAttack() const;
};
