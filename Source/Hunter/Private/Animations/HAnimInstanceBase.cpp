// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/HAnimInstanceBase.h"
#include "HBaseCharacter.h"

void UHAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* OwningPawn = TryGetPawnOwner();
	if (!OwningPawn) { return; }

	AHBaseCharacter* OwningCharacter = Cast<AHBaseCharacter>(OwningPawn);
	ensure(OwningCharacter);
	if (!OwningCharacter) { return; }

	CachedCharacterMode = OwningCharacter->GetCurrentCharacterMode();

}
