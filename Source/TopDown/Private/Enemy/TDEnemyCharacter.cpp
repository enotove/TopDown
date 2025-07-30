// Fill out your copyright notice in the Description page of Project Settings.

#include "C:\Users\DNS\Desktop\TopDown\Source\TopDown\Public\Components\TDHealthComponent.h"
#include "Enemy/TDEnemyCharacter.h"

// Sets default values
ATDEnemyCharacter::ATDEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UTDHealthComponent>("Health_Component");
	

}

// Called when the game starts or when spawned
void ATDEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


