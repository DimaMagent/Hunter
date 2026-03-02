// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HAICharacter.h"
#include "Components/WidgetComponent.h"
#include "UI/HGameUserWidget.h"
#include "AI/HEnemyAIController.h"

AHAICharacter::AHAICharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
	FrontHealthBarWidget = CreateDefaultSubobject<UWidgetComponent>("FrontHealthBarWidget");
	FrontHealthBarWidget->SetupAttachment(GetRootComponent());

	BackHealthBarWidget = CreateDefaultSubobject<UWidgetComponent>("BackHealthBarWidget");
	BackHealthBarWidget->SetupAttachment(GetRootComponent());
}

void AHAICharacter::BeginPlay()
{
	Super::BeginPlay();
	if (FrontHealthBarWidget) {
		UHGameUserWidget* Widget = Cast<UHGameUserWidget>(FrontHealthBarWidget->GetWidget());
		if (Widget) {
			Widget->InitWidgetPawnOwner(this);
		}
	}
	if (BackHealthBarWidget) {
		UHGameUserWidget* Widget = Cast<UHGameUserWidget>(BackHealthBarWidget->GetWidget());
		if (Widget) {
			Widget->InitWidgetPawnOwner(this);
		}
	}
}

void AHAICharacter::OnDeath()
{
	Super::OnDeath();
	if (FrontHealthBarWidget) {
		FrontHealthBarWidget->SetVisibility(false);
	}
	if (BackHealthBarWidget) {
		BackHealthBarWidget->SetVisibility(false);
	}
}
