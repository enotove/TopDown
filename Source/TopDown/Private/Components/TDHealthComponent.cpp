// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TDHealthComponent.h"

// Sets default values for this component's properties
UTDHealthComponent::UTDHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	

	// ...
}

float UTDHealthComponent::Get_Health() const
{
	return Health;
}

bool UTDHealthComponent::IsDead() const
{
	return Health <= 0.f;
}

bool UTDHealthComponent::AddHealth(float AddHealth)
{
	if (IsDead() || IsHealthFull())
	{
		return false;
	}
	Health = FMath::Clamp(Health + AddHealth, 0.f, Max_Health);
	OnHealthChanged.Broadcast(Health);
	return true;
	
}

bool UTDHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, Max_Health);
}


// Called when the game starts
void UTDHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = Max_Health;
	OnHealthChanged.Broadcast(Health);
	AActor* OwnerComponent = GetOwner();
	if (OwnerComponent)
	{
		OwnerComponent->OnTakeAnyDamage.AddDynamic(this, &UTDHealthComponent::OnTakeAnyDamage);
	}
}

void UTDHealthComponent::OnTakeAnyDamage(
	AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsDead())
		return;

	Health = FMath::Clamp(Health-Damage,0.f, Max_Health);
	OnHealthChanged.Broadcast(Health);
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}



