// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AnimNotifyState_MovementLock.h"
#include "HBaseCharacter.h"

void UAnimNotifyState_MovementLock::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp) { return; }

	AHBaseCharacter* Character = MeshComp->GetOwner<AHBaseCharacter>();
	if (!Character) { return; }

	Character->AddRestriction(EActionRestriction::BlockMove);

	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();

	if (!AnimInstance) { return; }
	AnimInstance->SetRootMotionMode(ERootMotionMode::RootMotionFromMontagesOnly);
}

void UAnimNotifyState_MovementLock::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp) { return; }

	AHBaseCharacter* Character = MeshComp->GetOwner<AHBaseCharacter>();
	if (!Character) { return; }

	Character->RemoveRestriction(EActionRestriction::BlockMove);

	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (!AnimInstance) { return; }
	AnimInstance->SetRootMotionMode(ERootMotionMode::IgnoreRootMotion);
}
