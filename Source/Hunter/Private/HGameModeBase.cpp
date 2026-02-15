// Fill out your copyright notice in the Description page of Project Settings.


#include "HGameModeBase.h"
#include "Player/HPlayerCharacter.h"
#include "Player/HPlayerController.h"

AHGameModeBase::AHGameModeBase()
{
	DefaultPawnClass = AHPlayerCharacter::StaticClass();
	PlayerControllerClass = AHPlayerController::StaticClass();
}
