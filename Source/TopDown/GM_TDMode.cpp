// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_TDMode.h"
#include "Public/Player/TDDefaultCharacter.h"
#include "Public/Player/TDPlayerController.h"
#include "UObject/ConstructorHelpers.h"
AGM_TDMode::AGM_TDMode()
{
	DefaultPawnClass = ATDDefaultCharacter::StaticClass();
	PlayerControllerClass = ATDPlayerController::StaticClass();
}