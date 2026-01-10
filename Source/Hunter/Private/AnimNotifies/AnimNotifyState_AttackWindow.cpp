// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AnimNotifyState_AttackWindow.h"
#include "HBaseCharacter.h"
#include "Components/HCombatComponent.h"

void UAnimNotifyState_AttackWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp) { return; }

	const AHBaseCharacter* Character = MeshComp->GetOwner<AHBaseCharacter>();
	if (!Character) { return; }

	UHCombatComponent* CombatComponent = Character->FindComponentByClass<UHCombatComponent>();
	if (!CombatComponent) {
		UE_LOG(LogAnimation, Error, TEXT("Character %s has not combat component"), *Character->GetName());
		return;
	}
	CombatComponent->OnAttackWindowBegin();
}

void UAnimNotifyState_AttackWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp) { return; }

	const AHBaseCharacter* Character = MeshComp->GetOwner<AHBaseCharacter>();
	if (!Character) { return; }

	UHCombatComponent* CombatComponent = Character->FindComponentByClass<UHCombatComponent>();
	if (!CombatComponent) {
		UE_LOG(LogAnimation, Error, TEXT("Character %s has not combat component"), *Character->GetName());
		return;
	}
	CombatComponent->OnAttackWindowEnd();
}
