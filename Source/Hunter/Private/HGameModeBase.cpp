// Fill out your copyright notice in the Description page of Project Settings.


#include "HGameModeBase.h"
#include "HBaseCharacter.h"
#include "HCharacterMovementComponent.h"
#include "Player/HPlayerController.h"

AHGameModeBase::AHGameModeBase()
{
	DefaultPawnClass = AHBaseCharacter::StaticClass();
	PlayerControllerClass = AHPlayerController::StaticClass();
}
