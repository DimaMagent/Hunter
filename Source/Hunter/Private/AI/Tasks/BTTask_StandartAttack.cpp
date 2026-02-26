// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_StandartAttack.h"
#include "AI/HEnemyAIController.h"
#include "HBaseCharacter.h"
#include "HCharacterMovementComponent.h"
#include "Components/HCombatComponent.h"

UBTTask_StandartAttack::UBTTask_StandartAttack()
{
	NodeName = TEXT("Standart Attack");
	bCreateNodeInstance = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_StandartAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CachedOwnerComp = &OwnerComp;
	
	UE_LOG(LogTemp, Display, TEXT("UBTTask_StandartAttack::ExecuteTask: CachedOwnerComp %s"), *CachedOwnerComp->GetName());

	AHEnemyAIController* Controller = Cast<AHEnemyAIController>(OwnerComp.GetAIOwner());

	if (!Controller) {return EBTNodeResult::Failed; }

	AHBaseCharacter* Character = Controller->GetPawn<AHBaseCharacter>();

	if (!Character) { return EBTNodeResult::Failed; }

	CachedCombatComponent = Character->GetCombatComponent();

	if (!CachedCombatComponent) { return EBTNodeResult::Failed; }
		
	UHCharacterMovementComponent* MovementComp = Cast<UHCharacterMovementComponent>(Character->GetCharacterMovement());

	if (!MovementComp) { return EBTNodeResult::Failed; }

	CachedCombatComponent->OnAttackInterrupted.AddUniqueDynamic(this, &UBTTask_StandartAttack::OnAttackInterrupted);

	bool bIsAttackStarted = Controller->OnAttack();

	if (bIsAttackStarted) {
		CachedCombatComponent->OnAttackEnded.AddUniqueDynamic(this, &UBTTask_StandartAttack::OnAttackEnded);
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("UBTTask_StandartAttack::ExecuteTask: OnAttack returned false, attack is not started"));
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_StandartAttack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	UE_LOG(LogTemp, Display, TEXT("UBTTask_StandartAttack::OnTaskFinished was called"));
	if (CachedCombatComponent) {
		CachedCombatComponent->OnAttackEnded.RemoveAll(this);
		CachedCombatComponent->OnAttackInterrupted.RemoveAll(this);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("UBTTask_StandartAttack::OnTaskFinished: CachedCombatComponent is nullptr, unregister OnAttackEnded is impossible"));
	}
	CachedOwnerComp = nullptr;
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

}

void UBTTask_StandartAttack::OnAttackEnded() {
	UE_LOG(LogTemp, Display, TEXT("UBTTask_StandartAttack::OnAttackEnded was called"));
	if (!CachedOwnerComp) { return; }
	FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Succeeded);
}

void UBTTask_StandartAttack::OnAttackInterrupted()
{
	UE_LOG(LogTemp, Display, TEXT("UBTTask_StandartAttack::OnAttackInterrupted was called"));
	if (!CachedOwnerComp) { return; }
	FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Failed);
}
