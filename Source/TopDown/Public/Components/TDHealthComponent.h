// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWN_API UTDHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTDHealthComponent();
	
	UFUNCTION(BlueprintCallable)
	float Get_Health() const;

	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

	bool AddHealth(float AddHealth);
	bool IsHealthFull() const;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Max_Health = 100.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
	

public:	
	
FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

private:
	float Health = 0.f;
	UFUNCTION()
	void OnTakeAnyDamage(
		AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
		
};
