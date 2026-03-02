// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/CombatTypes.h"
#include "HBaseWeapon.generated.h"


class UCapsuleComponent;
class AHBaseCharacter;

USTRUCT(BlueprintType)
struct FAttackData {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	EAttackId AttackType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", meta = (ClampMin = "0"))
	float DamageModifier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", meta = (ClampMin = "0"))
	float StaminaCostModifier;

};

USTRUCT(BlueprintType)
struct FSteps {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Combo")
	FName MontageSectionName;

	UPROPERTY(EditDefaultsOnly, Category = "Combo")
	FAttackData AttackData;
};

USTRUCT(BlueprintType)
struct FComboDefinition {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Combo")
	UAnimMontage* ComboMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combo")
	TArray<FSteps> ComboSteps;

	FSteps GetCurrentComboStep() const { return ComboSteps[CurrentComboStep]; }

	FAttackData GetCurrentComboAttackData() const { return ComboSteps[CurrentComboStep].AttackData; }

	void NextCombo() { CurrentComboStep = (CurrentComboStep + 1) % ComboSteps.Num(); }

	void ClearCombo() { CurrentComboStep = 0; }

private:
	int32 CurrentComboStep = 0;
};

UCLASS(Abstract)
class HUNTER_API AHBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AHBaseWeapon();

	EMoveSet GetMoveSet() const { return WeaponMoveSet; }

	virtual void AttackDataHandle(EAttackIntent AttackIntent);

	void SetCollsionMode(ECollisionResponse NewMode);

	void NextComboDataHandle(bool IsComboInputBuffered);

	void OnComboEnded();

	void OnAttackWindowEnd();

	UAnimMontage* GetCurrentComboAnim(EAttackIntent AttackIntent) const;

	bool GetCurrentStepName(FName& OutStepName) const;

	float GetCurrentStaminaCost() const { return CurrentStaminaCost; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float BaseDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float BaseStaminaCost = 10.0f;

	UFUNCTION()
	virtual void OnWeaponCollision(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	EMoveSet WeaponMoveSet = EMoveSet::Unarmed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	TMap<EAttackIntent, FComboDefinition> WeaponAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collision")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

private:
	UPROPERTY()
	TArray<TObjectPtr<AHBaseCharacter>> CharactersCollisionIgnored;

	EAttackIntent LastAttackIntent;

	float CurrentDamage = 0.0f;

	float CurrentStaminaCost = 0.0f;

};
