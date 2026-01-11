#pragma once

#include "CoreMinimal.h"
#include "WeaponTypes.generated.h"

UENUM(BlueprintType) 
enum class EMoveSet : uint8 {
	Sword,
	Unarmed
};

UENUM(BlueprintType)
enum class EAttackType : uint8 {
	Light,
	Heavy
};

USTRUCT(BlueprintType)
struct FAttackInfo {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float DamageModifier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float StaminaCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float AttackCooldown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	EAttackType AttackType;
};
