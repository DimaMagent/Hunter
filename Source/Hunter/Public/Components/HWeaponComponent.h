// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/WeaponTypes.h"
#include "Types/CombatTypes.h"
#include "HWeaponComponent.generated.h"

class AHBaseWeapon;
class AHBaseCharacter;
class UHCombatComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTryAttackInterrupt);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTER_API UHWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHWeaponComponent();

	void BeginAttack(EAttackIntent CurrentAttackIntent) const;

	void ContinueCombo(bool IsComboInputBuffered);

	void BeginParrying();

	void OnComboEnded();

	EMoveSet GetMoveSet() const;

	void OnAttackWindowBegin();

	void OnAttackWindowEnd();

	FOnTryAttackInterrupt OnTryAttackInterrupt;

protected:
	virtual void BeginPlay() override;

	void SetWeaponCollisionMode(ECollisionResponse NewMode);

	UFUNCTION()
	virtual void OnCharacterDead();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AHBaseWeapon> DefaultWeaponClass;

	UPROPERTY()
	TObjectPtr<AHBaseWeapon> CurrentWeapon;
private:

	UPROPERTY()
	TObjectPtr<AHBaseCharacter> CachedOwner;

		
};
