// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "TDReloadFinishedAnimNotify.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifyReloadFinishedSignature, USkeletalMeshComponent*);
/**
 * 
 */
UCLASS()
class TOPDOWN_API UTDReloadFinishedAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	FOnNotifyReloadFinishedSignature OnNotifyReloadFinished;
};
