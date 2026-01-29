// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/WeaponTypes.h"
#include "Types/CombatTypes.h"
#include "HWeaponComponent.generated.h"

class AHBaseWeapon;
class AHBaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTER_API UHWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHWeaponComponent();

	void BeginAttack(EAttackIntent CurrentAttackIntent) const;

	void TryBeginAttack(EAttackIntent CurrentAttackIntent) const;

	void ContinueCombo(bool IsComboInputBuffered);

	void Notify_OnComboEnd();

	EMoveSet GetMoveSet() const;

	void SetWeaponCollisionMode(ECollisionResponse NewMode);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AHBaseWeapon> DefaultWeaponClass;

	UPROPERTY()
	TObjectPtr<AHBaseWeapon> CurrentWeapon;
private:

	UPROPERTY()
	TObjectPtr<AHBaseCharacter> CachedOwner;
		
};
