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


/*
явл€етс€ классом дл€ игрока, пока нет других character
*/
UCLASS()
class HUNTER_API AHBaseCharacter : public ACharacter, public IHWeaponOwnerInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Mode")
	FOnCharacterModeChanged OnCharacterModeChanged;

	FOnCharacterRecover OnCharacterRecovery;

	AHBaseCharacter(const FObjectInitializer& ObjectInitializer);

	void Move(const FVector2D MoveAroundValue);
	void LookAround(const FVector2D LookAxisValue);
	void Attack(EAttackIntent AttackIntent);
	void RunStart();
	void RunEnd();
	virtual void PlayAttackAnim(UAnimMontage* AttackAnimMontage);
	void PlayComboStep(FName StepName) const;
	void ChangeStamina(float Count);
	void TakeDamage(float Count);
	bool IsAnyAnimMontageActive() const { return bIsAnimMontageActive; }
	bool IsCharacterAlive() const;
	bool IsCharacterHasStamina() const;

	virtual UHWeaponComponent* GetWeaponComponent_Implementation() const override { return WeaponComponent; };

	ECharacterMode GetCurrentCharacterMode() const { return CharacterMode; }

protected:

	virtual void BeginPlay() override;

	void Recovery();

	FTimerHandle CharacterRecoveryTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

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

private:

	UPROPERTY()
	TObjectPtr<UHCharacterMovementComponent> CachedMovementComponent;

	UPROPERTY()
	TObjectPtr<UHAnimInstanceBase> CachedAnimInstance;

	bool bIsAnimMontageActive = false;

	EMovementMode PreviousMovementMode;

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void EnsureFightMode();
	void ChangeCharacterMode(ECharacterMode NewMode);
	void TryEnterFightMode();
	void UpdateLookAroundMode();
	void Caching();


};
