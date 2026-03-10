// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UHUIMessageSubsystem.generated.h"

UENUM()
enum class EMainMenuEvent : uint8
{
	Start,
	Exit
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMenuEvent, EMainMenuEvent, MenuEvent);
/**
 * 
 */
UCLASS()
class HUNTER_API UUHUIMessageSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	void BroadcastMenuEvent(EMainMenuEvent MenuEvent);

	void RemoveMenuEvent(const UObject* Object);

	FOnMenuEvent OnMenuEvent;
	
};
