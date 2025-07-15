// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TDPlayerController.h"

ATDPlayerController::ATDPlayerController() {}

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
void ATDPlayerController::BeginSpectatingState()
{
	SetControlRotation(FRotator(-75.f, 0.f, 0.f));
	Super::BeginSpectatingState();
}