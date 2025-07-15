// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/TDReloadFinishedAnimNotify.h"

void UTDReloadFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotifyReloadFinished.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}