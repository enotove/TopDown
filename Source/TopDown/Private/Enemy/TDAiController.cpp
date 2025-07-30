// Fill out your copyright notice in the Description page of Project Settings.

#include "C:\Users\DNS\Desktop\TopDown\Source\TopDown\Public\Enemy\TDEnemyCharacter.h"
#include "Enemy/TDAiController.h"

void ATDAiController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	const auto AICharacter = Cast<ATDEnemyCharacter>(InPawn);
	if (AICharacter)
	{
		RunBehaviorTree(AICharacter->BehaviorTreeAsset);
	}
}