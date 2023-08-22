// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DELEGATE_RetVal(bool, FOnDeathDelegate)
DECLARE_DELEGATE_OneParam(FOnNewHealth, int32)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_TEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Health")
	int32 MaxHealth=100;

	virtual void InitializeComponent() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );
public:
	FOnDeathDelegate& GetDeathDelegate() {return OnDeath;}
	
	void SetHealth(int32 NewHealth);
private:
	int32 CurrentHealth;
	FOnDeathDelegate OnDeath;
		
};
