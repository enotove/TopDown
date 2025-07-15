// Fill out your copyright notice in the Description page of Project Settings.


#include "TDHealthPickup.h"
#include <Components/SphereComponent.h>
#include <GameFramework/Actor.h>
#include "C:\Users\DNS\Desktop\TopDown\Source\TopDown\Public\Player\TDDefaultCharacter.h"
#include "C:\Users\DNS\Desktop\TopDown\Source\TopDown\Public\Components\TDHealthComponent.h"

// Sets default values
ATDHealthPickup::ATDHealthPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(SphereComponent);

}

// Called when the game starts or when spawned
void ATDHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATDHealthPickup::GivePickup(ATDDefaultCharacter* Character)
{
	const auto HealthComponent = Character->GetHealthComponent();
	if (!HealthComponent)
		return false;
	return HealthComponent->AddHealth(HealthFromPickup);
}

void ATDHealthPickup::PickupWasTaken() 
{
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetRootComponent()->SetVisibility(false, true);
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ATDHealthPickup::RespawnPickup, RespawnTime);

}

void ATDHealthPickup::RespawnPickup()
{
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GetRootComponent()->SetVisibility(true, true);
}

void ATDHealthPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
	const auto Character = Cast<ATDDefaultCharacter>(OtherActor);
	if (GivePickup(Character))
	{
		PickupWasTaken();
	}
}
