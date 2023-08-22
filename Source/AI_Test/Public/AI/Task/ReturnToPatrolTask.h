// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ReturnToPatrolTask.generated.h"



UCLASS()
class AI_TEST_API UReturnToPatrolTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UReturnToPatrolTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector CurrentTaskKey;
};
