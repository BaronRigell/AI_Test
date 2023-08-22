// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TestAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/AICharacter.h"
#include "Component/TestAIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"


ATestAIController::ATestAIController()
{
	PerceptionComp = CreateDefaultSubobject<UTestAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*PerceptionComp);
}

void ATestAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<AAICharacter>(InPawn);
	if (AICharacter && BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
		const auto Bboard = GetBlackboardComponent();
		if (!Bboard) return;
		
		Bboard->SetValueAsEnum(CurrentTaskKey.SelectedKeyName, Patrol);
	}
}

void ATestAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ATestAIController::OnCharacterSensed);
	PerceptionComp->OnTargetPerceptionForgotten.AddDynamic(this, &ATestAIController::OnCharacterUnSensed);
}

void ATestAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	PerceptionComp->OnTargetPerceptionUpdated.RemoveDynamic(this, &ATestAIController::OnCharacterSensed);
	PerceptionComp->OnTargetPerceptionForgotten.RemoveDynamic(this, &ATestAIController::OnCharacterUnSensed);
	
	Super::EndPlay(EndPlayReason);
}

void ATestAIController::OnCharacterSensed(AActor* TargetActor, FAIStimulus StimulusStore)
{
	if (TargetActor && TargetActor->IsA<ACharacter>())
	{
		const auto Config = PerceptionComp->GetSenseConfig(StimulusStore.Type);
		if (!Config) return;
		
		const auto ConfigSense = Config->GetSenseImplementation();
		if (!ConfigSense) return;
		
		const auto Bboard = GetBlackboardComponent();
		if (!Bboard) return;
		
		Bboard->SetValueAsObject(SensedCharacterKey.SelectedKeyName, TargetActor);
		Bboard->SetValueAsVector(LastSensedLocationKey.SelectedKeyName,
			StimulusStore.StimulusLocation);
		const auto CurrentState = Bboard->GetValueAsEnum(CurrentTaskKey.SelectedKeyName);
		if (StimulusStore.WasSuccessfullySensed())
		{
			if (ConfigSense->IsChildOf<UAISense_Sight>())
			{
				Bboard->SetValueAsEnum(CurrentTaskKey.SelectedKeyName, EEnemyState::Follow);
			}
			if (ConfigSense->IsChildOf<UAISense_Hearing>() && CurrentState != Follow)
			{
				Bboard->SetValueAsEnum(CurrentTaskKey.SelectedKeyName, EEnemyState::SearchNoise);
			}
		}
		else
		{
			if (CurrentState == Follow)
			{
				//Bboard->SetValueAsEnum(CurrentTaskKey.SelectedKeyName, EEnemyState::Find);
			}
		}
	}
}

void ATestAIController::OnCharacterUnSensed(AActor* TargetActor)
{
	const auto Bboard = GetBlackboardComponent();
	if (!Bboard) return;
	
	Bboard->SetValueAsObject(SensedCharacterKey.SelectedKeyName, nullptr);
}
