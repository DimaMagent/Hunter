// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HEnemyAIController.generated.h"

class AHBaseCharacter;
class UAIPerceptionComponent;
class UBehaviorTree;
/**
 * 
 */
UCLASS()
class HUNTER_API AHEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:

	AHEnemyAIController();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* PawnToPossess) override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	AHBaseCharacter* GetControlledCharacter() const { return CachedCharacter; }

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void OnAttack() const;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void OnAlternativeAttack() const;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void OnRunStart() const;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void OnRunEnd() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	
private:

	UPROPERTY()
	TObjectPtr<AHBaseCharacter> CachedCharacter;
	
};
