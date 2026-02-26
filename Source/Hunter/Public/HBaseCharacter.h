// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/CharacterTypes.h"
#include "Interfaces/HWeaponOwnerInterface.h"
#include "Types/CombatTypes.h"
#include "HBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UHCharacterMovementComponent;
class UHHealthComponent;
class UHCombatComponent;
class UHWeaponComponent;
class UHAnimInstanceBase;
class UHStaminaComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterModeChanged, ECharacterMode, NewMode);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterRecover);

UENUM()
enum class EActionRestriction : int32 {
	None = 0,
	BlockMove = 1 << 0,
	BlockAttack = 1 << 1,
};
ENUM_CLASS_FLAGS(EActionRestriction);
/*
*/
UCLASS(Abstract)
class HUNTER_API AHBaseCharacter : public ACharacter, public IHWeaponOwnerInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Mode")
	FOnCharacterModeChanged OnCharacterModeChanged;

	FOnCharacterRecover OnCharacterRecovery;

	AHBaseCharacter(const FObjectInitializer& ObjectInitializer);

	/*Any system that adds a restriction must remove it.
If you want to select multiple restriction, you should use  | operation*/
	void AddRestriction(EActionRestriction Restriction) { ActiveRestrictions |= Restriction; }

	void RemoveRestriction(EActionRestriction Restriction) { ActiveRestrictions &= (~Restriction); }

	bool HasInputRestriction(EActionRestriction Restriction) const;

	UHCombatComponent* GetCombatComponent() const { return CombatComponent; }

	void Move(const FVector2D MoveAroundValue);
	void LookAround(const FVector2D LookAxisValue);
	bool Attack(EAttackIntent AttackIntent);
	void RunStart();
	void RunEnd();

	virtual bool PlayAnim(UAnimMontage* AttackAnimMontage);
	void PlayComboStep(FName StepName) const;

	void ChangeStamina(float Count);
	void ReceiveDamage(float Count);

	bool IsAnyAnimMontageActive() const { return bIsAnimMontageActive; }
	bool IsCharacterAlive() const;
	bool IsCharacterHasStamina() const;

	virtual UHWeaponComponent* GetWeaponComponent_Implementation() const override { return WeaponComponent; };

	ECharacterMode GetCurrentCharacterMode() const { return CharacterMode; }

protected:

	virtual void BeginPlay() override;

	virtual void Recovery() const;

	void EnsureFightMode();
	void ChangeCharacterMode(ECharacterMode NewMode);
	void TryEnterFightMode();

	void UpdateLookAroundMode();

	void Caching();

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	EMovementMode PreviousMovementMode;

	bool bIsAnimMontageActive = false;

	FTimerHandle CharacterRecoveryTimer;

	EActionRestriction ActiveRestrictions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UHHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UHCombatComponent> CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UHWeaponComponent> WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UHStaminaComponent> StaminaComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recovery")
	float RecoveryRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recovery")
	float RecoveryDelay = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mode")
	ECharacterMode CharacterMode;

	UPROPERTY()
	TObjectPtr<UHCharacterMovementComponent> CachedMovementComponent;

	UPROPERTY()
	TObjectPtr<UHAnimInstanceBase> CachedAnimInstance;

};
