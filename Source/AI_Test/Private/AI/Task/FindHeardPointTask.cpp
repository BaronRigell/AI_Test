// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\AI\Task\FindHeardPointTask.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindHeardPointTask::UFindHeardPointTask()
{
	NodeName = "Find New Heard Location";
}

EBTNodeResult::Type UFindHeardPointTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if (!NavSys) return EBTNodeResult::Failed;
		
	FNavLocation NewLocation;
	NavSys->GetRandomReachablePointInRadius(Blackboard->GetValueAsVector(HeardLocationKey.SelectedKeyName),
		Radius, NewLocation);
	Blackboard->SetValueAsVector(CheckHeardLocationKey.SelectedKeyName,NewLocation.Location);
	
	return EBTNodeResult::Succeeded;
}
