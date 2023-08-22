// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/ReturnToPatrolTask.h"
#include "AI/TestAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UReturnToPatrolTask::UReturnToPatrolTask()
{
	NodeName="Return To Patrol";
}

EBTNodeResult::Type UReturnToPatrolTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Bboard = OwnerComp.GetBlackboardComponent();
	if (!Bboard) return EBTNodeResult::Failed;
		
	Bboard->SetValueAsEnum(CurrentTaskKey.SelectedKeyName, Patrol);
	return EBTNodeResult::Succeeded;
}
