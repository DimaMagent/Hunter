#pragma once
#include "CoreMinimal.h"
#include "CombatTypes.generated.h"

UENUM()
enum class EAttackIntent : int32 {
	Standart,
	Alternative,
};

UENUM()
enum class EAttackId : int32 {
	None,
	Light1,
	Light2,
	Heavy,
	StandaloneHeavy
};

UENUM(BlueprintType)
enum class EMoveSet : uint8 {
	Unarmed,
	Sword
};