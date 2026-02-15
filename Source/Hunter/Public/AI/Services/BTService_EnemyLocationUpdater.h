// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_EnemyLocationUpdater.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UBTService_EnemyLocationUpdater : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_EnemyLocationUpdater();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (ToolTip = "Name of the actor key whose location needs to be updated"))
	FBlackboardKeySelector EnemyActorKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (ToolTip = "Name of key into which the updated location should be written"))
	FBlackboardKeySelector EnemyLocationKey;

};
