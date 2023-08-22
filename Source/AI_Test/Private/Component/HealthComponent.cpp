
#include "Component/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent=true;
}

void UHealthComponent::InitializeComponent()
{
	Super::InitializeComponent();

	CurrentHealth=MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
}

void UHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnDeath.Unbind();
	GetOwner()->OnTakeAnyDamage.Clear();
	Super::EndPlay(EndPlayReason);
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (GetOwner() && DamagedActor==GetOwner()) SetHealth(FMath::TruncToInt32(Damage));
}

void UHealthComponent::SetHealth(int32 NewHealth)
{
	NewHealth = FMath::Clamp<int32>(NewHealth, 0, MaxHealth);
	CurrentHealth = NewHealth;
	if (CurrentHealth<=0)
	{
		if (OnDeath.IsBound())
			OnDeath.Execute();
	}
}

