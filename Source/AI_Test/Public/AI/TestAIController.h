// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "TestAIController.generated.h"

struct FAIStimulus;
class UTestAIPerceptionComponent;

UENUM(BlueprintType)
enum EEnemyState : uint8
{
	None	UMETA(Hidden),
	Patrol,
	SearchNoise UMETA(DisplayName="Search"),
	Find UMETA(Hidden),
	Follow 
};

UCLASS()
class AI_TEST_API ATestAIController : public AAIController
{
	GENERATED_BODY()
public:
	ATestAIController();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Behavior Tree")
	UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Perception")
	UTestAIPerceptionComponent* PerceptionComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Blackboard")
	FBlackboardKeySelector SensedCharacterKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Blackboard")
	FBlackboardKeySelector LastSensedLocationKey;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Blackboard")
	FBlackboardKeySelector CurrentTaskKey;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UFUNCTION()
	void OnCharacterSensed(AActor* TargetActor, FAIStimulus StimulusStore);
	UFUNCTION()
	void OnCharacterUnSensed(AActor* TargetActor);
};
