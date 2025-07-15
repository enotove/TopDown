// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDHealthPickup.generated.h"

class USphereComponent;
class ATDDefaultCharacter;

UCLASS()
class TOPDOWN_API ATDHealthPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDHealthPickup();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	USphereComponent* SphereComponent;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 5.f;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float HealthFromPickup = 100.f;
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool GivePickup(ATDDefaultCharacter* Character);
	void PickupWasTaken();
	void RespawnPickup();

};
