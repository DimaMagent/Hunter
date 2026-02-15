// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HEnemyAIController.h"
#include "HBaseCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AHEnemyAIController::AHEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
}

void AHEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	ensureMsgf(BehaviorTree, TEXT("BehaviorTree is not set on %s"), *GetName());

	if (BehaviorTree) {
		RunBehaviorTree(BehaviorTree);
	}
}

void AHEnemyAIController::OnPossess(APawn* PawnToPossess)
{
	Super::OnPossess(PawnToPossess);
	CachedCharacter = Cast<AHBaseCharacter>(PawnToPossess);
}

void AHEnemyAIController::OnAttack() const
{
	if (!CachedCharacter) { return; }
	CachedCharacter->Attack(EAttackIntent::Standart);
}

void AHEnemyAIController::OnAlternativeAttack() const
{
	if (!CachedCharacter) { return; }
	CachedCharacter->Attack(EAttackIntent::Alternative);
}

void AHEnemyAIController::OnRunStart() const
{
	if (!CachedCharacter) { return; }
	CachedCharacter->RunStart();
}

void AHEnemyAIController::OnRunEnd() const
{
	if (!CachedCharacter) { return; }
	CachedCharacter->RunEnd();
}

