// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HHealthComponent.h"

UHHealthComponent::UHHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UHHealthComponent::TakeDamage(float DamageAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
}


void UHHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UHHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

