// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindHeardPointTask.generated.h"


UCLASS()
class AI_TEST_API UFindHeardPointTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFindHeardPointTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(ClampMin=0, ClampMax=5000))
	float Radius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector CheckHeardLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector HeardLocationKey;
};
