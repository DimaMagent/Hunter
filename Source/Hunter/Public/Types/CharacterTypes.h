#pragma once

#include "CoreMinimal.h"
#include "CharacterTypes.generated.h"

UENUM(BlueprintType)
enum class ECharacterMode : uint8 
{
	AdventureMode,
	FightMode
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterModeChanged, ECharacterMode, NewMode);