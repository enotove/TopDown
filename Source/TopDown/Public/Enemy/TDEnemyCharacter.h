// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDEnemyCharacter.generated.h"

class UTDHealthComponent;
class UBehaviorTree;
UCLASS()
class TOPDOWN_API ATDEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATDEnemyCharacter();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTDHealthComponent* HealthComponent;
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
