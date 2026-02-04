// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HStaminaComponent.h"
#include "HBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(StaminaComponentLog, All, All)

UHStaminaComponent::UHStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHStaminaComponent::ChangeStamina(float Count)
{
	if (Count == 0) { return; }
	CurrentStamina = FMath::Clamp(CurrentStamina + Count, 0.0f, MaxStamina);
	if (GetOwner()) {
		UE_LOG(LogTemp, Display, TEXT("%s: Current stamina: %f"), *GetOwner()->GetName(), CurrentStamina);
	}
	if (FMath::IsNearlyZero(CurrentStamina)) {
		TrySettingStaminaRecoveryPenalty();
	}
	OnStaminaChanged.Broadcast(GetStaminaPercent());
}



void UHStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentStamina = MaxStamina;

	CachedCharacter = GetOwner<AHBaseCharacter>();
	ensure(CachedCharacter);

	if (CachedCharacter) {
		CachedCharacter->OnCharacterRecovery.AddDynamic(this, &UHStaminaComponent::OnRecovery);
	}
}

void UHStaminaComponent::OnRecovery()
{
	if (!bCanStaminaRecovery) { return; }
	ChangeStamina(StaminaRecoveryCount);
}

void UHStaminaComponent::TrySettingStaminaRecoveryPenalty()
{
	UWorld* World = GetWorld();
	if (!World) { return; }

	bCanStaminaRecovery = false;

	World->GetTimerManager().SetTimer(StaminaRecoveryPenaltyTimer, this, &UHStaminaComponent::StaminaRecoveryPenaltyClear, StaminaRecoveryPenaltyDuration, false);

	OnStaminaRecoveryPenalty.Broadcast();
}

void UHStaminaComponent::StaminaRecoveryPenaltyClear()
{
	bCanStaminaRecovery = true;
	UE_LOG(StaminaComponentLog, Display, TEXT("Stamina recover penalty is clear"));
}

