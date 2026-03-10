// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HMainMenuWidget.h"
#include "Components/Button.h"
#include "Subsystems/UHUIMessageSubsystem.h"


void UHMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartButton) {
		StartButton->OnClicked.AddDynamic(this, &UHMainMenuWidget::StartButtonClicked);
	}
	if (ExitButton) {
		ExitButton->OnClicked.AddDynamic(this, &UHMainMenuWidget::ExitButtonClicked);
	}
}

void UHMainMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UUHUIMessageSubsystem* UIMessageSubsystem = GetUIMessageSubsystem();
	if (!UIMessageSubsystem) {
		UE_LOG(LogTemp, Error, TEXT("UHMainMenuWidget::NativeDestruct: UIMessageSubsystem is nullptr!"));
		return;
	}
	UIMessageSubsystem->RemoveMenuEvent(this);
}

void UHMainMenuWidget::StartButtonClicked()
{
	UUHUIMessageSubsystem* UIMessageSubsystem = GetUIMessageSubsystem();
	if (!UIMessageSubsystem) {
		UE_LOG(LogTemp, Error, TEXT("UHMainMenuWidget::StartButtonClicked: UIMessageSubsystem is nullptr!"));
		return;
	}

	UIMessageSubsystem->BroadcastMenuEvent(EMainMenuEvent::Start);
}

void UHMainMenuWidget::ExitButtonClicked()
{
	UUHUIMessageSubsystem* UIMessageSubsystem = GetUIMessageSubsystem();
	if (!UIMessageSubsystem) {
		UE_LOG(LogTemp, Error, TEXT("UHMainMenuWidget::StartButtonClicked: UIMessageSubsystem is nullptr!"));
		return;
	}
	UIMessageSubsystem->BroadcastMenuEvent(EMainMenuEvent::Exit);
}

UUHUIMessageSubsystem* UHMainMenuWidget::GetUIMessageSubsystem()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance) {
		UE_LOG(LogTemp, Error, TEXT("UHMainMenuWidget::GetUIMessageSubsystem: GameInstance is nullptr!"));
		return nullptr;
	}
	UUHUIMessageSubsystem* UIMessageSubsystem = GameInstance->GetSubsystem<UUHUIMessageSubsystem>();
	return UIMessageSubsystem;
}
