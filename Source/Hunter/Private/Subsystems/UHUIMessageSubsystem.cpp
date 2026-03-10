// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/UHUIMessageSubsystem.h"

void UUHUIMessageSubsystem::BroadcastMenuEvent(EMainMenuEvent MenuEvent)
{
	OnMenuEvent.Broadcast(MenuEvent);
}

void UUHUIMessageSubsystem::RemoveMenuEvent(const UObject* Object)
{
	OnMenuEvent.RemoveAll(Object);
}
