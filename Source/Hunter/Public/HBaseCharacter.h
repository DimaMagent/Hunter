// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/CharacterTypes.h"
#include "Interfaces/HWeaponOwnerInterface.h"
#include "Types/WeaponTypes.h"
#include "HBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UHCharacterMovementComponent;
class UHHealthComponent;
class UHCombatComponent;
class UHWeaponComponent;
struct FInputActionInstance;
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

	AHBaseCharacter(const FObjectInitializer& ObjectInitializer);

	void Move(const FVector2D MoveAroundValue);
	void LookAround(const FVector2D LookAxisValue);
	void Attack();
	void RunStart();
	void RunEnd();
	virtual void PlayAttackAnim(EMoveSet CurrentMoveSet) const;

	virtual UHWeaponComponent* GetWeaponComponent_Implementation() const override { return WeaponComponent; };

	ECharacterMode GetCurrentCharacterMode() const { return CharacterMode; };

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UHHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UHCombatComponent> CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UHWeaponComponent> WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mode")
	ECharacterMode CharacterMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
	TMap<EMoveSet, UAnimMontage*> AttackAnims;

private:

	UPROPERTY()
	TObjectPtr<UHCharacterMovementComponent> CachedMovementComponent;

	void EnsureFightMode();
	void ChangeCharacterMode(ECharacterMode NewMode);
	void TryEnterFightMode();
	void UpdateLookAroundMode();
};
