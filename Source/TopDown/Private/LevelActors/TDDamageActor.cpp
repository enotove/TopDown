// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelActors/TDDamageActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATDDamageActor::ATDDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereComponent = CreateDefaultSubobject<USphereComponent>("RadiusDamage");
	sphereComponent->SetSphereRadius(SphereRadius);
	SetRootComponent(sphereComponent);

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(sphereComponent);
	mesh->SetRelativeScale3D(FVector(2.f, 2.f, 0.05f));
	mesh->SetRelativeLocation(FVector(0.f, 0.f, -4.f));
}

// Called when the game starts or when spawned
void ATDDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), SphereRadius, nullptr, {}, this, nullptr, false);
}

