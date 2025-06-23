// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TDPlayerController.h"

ATDPlayerController::ATDPlayerController() {}

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}