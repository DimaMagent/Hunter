// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HGameUserWidget.h"
#include "Components/HHealthComponent.h"
#include "Components/HStaminaComponent.h"

void UHGameUserWidget::UpdateCurrentHealthPercent(float NewStaminaPercent)
{
	CachedHealthPercent = NewStaminaPercent;
}

void UHGameUserWidget::UpdateCurrentStaminaPercent(float NewHealthPercent)
{
	CachedStaminaPercent = NewHealthPercent;
}

void UHGameUserWidget::InitWidgetPawnOwner(APawn* NewWidgetPawnOwner)
{
	if (!NewWidgetPawnOwner) {
		UE_LOG(LogTemp, Error, TEXT("Method InitWidgetPawnOwner: NewWidgetPawnOwner is nullptr!"));
		return;
	}
	CachedWidgetPawnOwner = NewWidgetPawnOwner;
}

void UHGameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CachedWidgetPawnOwner) {
		CachedHealthComponent = CachedWidgetPawnOwner->FindComponentByClass<UHHealthComponent>();
		CachedStaminaComponent = CachedWidgetPawnOwner->FindComponentByClass<UHStaminaComponent>();

		if (CachedHealthComponent) {
			CachedHealthComponent->OnHealthChanged.AddDynamic(this, &UHGameUserWidget::UpdateCurrentHealthPercent);
		}
		if (CachedStaminaComponent) {
			CachedStaminaComponent->OnStaminaChanged.AddDynamic(this, &UHGameUserWidget::UpdateCurrentStaminaPercent);
			CachedStaminaComponent->OnStaminaRecoveryPenalty.AddDynamic(this, &UHGameUserWidget::OnStaminaRecoveryPenalty);
		}
	}
}
