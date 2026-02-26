// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_StandartAttack.generated.h"

class AHBaseCharacter;
class UBehaviorTreeComponent;
class UHCombatComponent;
/**
 * 
 */
UCLASS()
class HUNTER_API UBTTask_StandartAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_StandartAttack();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	UFUNCTION()
	virtual void OnAttackEnded();

	UFUNCTION()
	virtual void OnAttackInterrupted();

	UPROPERTY()
	TObjectPtr<UHCombatComponent> CachedCombatComponent;
	
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> CachedOwnerComp;
};
