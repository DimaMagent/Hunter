// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_EnemyLocationUpdater.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_EnemyLocationUpdater::UBTService_EnemyLocationUpdater()
{
	bNotifyTick = true;
}

void UBTService_EnemyLocationUpdater::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BlacboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlacboardComponent) { return; }

	AActor* EnemyActor = Cast<AActor>(BlacboardComponent->GetValueAsObject(EnemyActorKey.SelectedKeyName));
	if (!EnemyActor) { return; }

	FVector EnemyLocation = EnemyActor->GetActorLocation();
	BlacboardComponent->SetValueAsVector(EnemyLocationKey.SelectedKeyName, EnemyLocation);
}
