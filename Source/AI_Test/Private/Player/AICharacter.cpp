// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AICharacter.h"
#include "AI_Test/Public/Component/HealthComponent.h"

AAICharacter::AAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

void AAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HealthComponent->GetDeathDelegate().BindUObject(this, &AActor::Destroy, false, false);
}

void AAICharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	
	
	Super::EndPlay(EndPlayReason);
}



