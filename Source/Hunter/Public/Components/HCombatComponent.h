// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/CombatTypes.h"
#include "HCombatComponent.generated.h"

class AHBaseCharacter;
class UHWeaponComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTER_API UHCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHCombatComponent();
	void TryAttack(EAttackIntent AttackIntent);
	void Notify_OnAttackWindowBegin();
	void Notify_OnAttackWindowEnd();

	void Notify_OnComboWindowBegin();
	void Notify_OnComboWindowEnd();
	
	void Notify_OnEndCombo();

protected:
	virtual void BeginPlay() override;

	bool bComboInputAllowed = false;
	bool bComboInputBuffered = false;

private:
	UPROPERTY()
	TObjectPtr<AHBaseCharacter> CachedCharacter;

	UPROPERTY()
	TObjectPtr<UHWeaponComponent> CachedWeaponComponent;

	bool CanAttack() const;
	bool IsAttackInProgress() const;

	bool IsOwnerAlive() const;
	bool IsOwnerHasStamina() const;
};
