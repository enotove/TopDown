// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/TDWeaponComponent.h"
#include "Weapon/TDBaseWeapon.h"
#include <GameFramework/Character.h>
#include "C:\Users\DNS\Desktop\TopDown\Source\TopDown\Public\Animations\TDReloadFinishedAnimNotify.h"
#include <Animation\AnimMontage.h>



// Sets default values for this component's properties
UTDWeaponComponent::UTDWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	

	// ...
}


// Called when the game starts
void UTDWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
	InitAnimNotify();
	if (Weapon)
	{
		Weapon->BulletsEmpty.AddUObject(this, &UTDWeaponComponent::Reload);
	}
	// ...
	
}


void UTDWeaponComponent::InitAnimNotify() {
	
	if (!ReloadMontage)
	{ 
		return;
	}
	
	const auto NotifiesEvents = ReloadMontage->Notifies;
	for (auto NotifyEvent : NotifiesEvents)
	{
		auto ReloadFinish = Cast<UTDReloadFinishedAnimNotify>(NotifyEvent.Notify);
		if (ReloadFinish)
		{
			ReloadFinish->OnNotifyReloadFinished.AddUObject(this, &UTDWeaponComponent::OnNotifyReloadFinished);
			break;
		}
	}
}
void UTDWeaponComponent::OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh) {
	const auto Character = Cast<ACharacter>(GetOwner());
	if (Character->GetMesh() == SkeletalMesh)
	{
		AnimReloading = false;
	}
}

bool UTDWeaponComponent::CanReload() const
{
	return !AnimReloading && !Weapon->IsCurrentBulletsFull();
	
}
void UTDWeaponComponent::Reload()
{
	if (!CanReload() )
		return;
	Weapon->ChangeClip();
	AnimReloading = true;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->PlayAnimMontage(ReloadMontage);
}
// Called every frame
void UTDWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTDWeaponComponent::StartFire() 
{
	if (!Weapon || AnimReloading || Weapon->IsCurrentClipEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, FString::Printf(TEXT("Start Fire is Wrong")));
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, FString::Printf(TEXT("Start Fire is Medium")));
	GetWorld()->GetTimerManager().SetTimer(
		FiresTimerHandle, this, &UTDWeaponComponent::FireTickon, Weapon->GetSpeedFire(), true, Weapon->GetSpeedFire());
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, FString::Printf(TEXT("Start Fire is Success")));
}
	


void UTDWeaponComponent::StopFire() 
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, FString::Printf(TEXT("StopFire")));
	GetWorld()->GetTimerManager().ClearTimer(FiresTimerHandle);
}

void UTDWeaponComponent::FireTickon()
{
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Purple, FString::Printf(TEXT("FireTickon")));
	if (!Weapon || AnimReloading || Weapon->IsCurrentClipEmpty())
	{
		
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Purple, FString::Printf(TEXT("FireTick")));
		StopFire();
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, FString::Printf(TEXT("FireTickElse")));
	Weapon->Fire();

}

bool UTDWeaponComponent::Get_Current_Ammo(FAmmoWeapon& AmmoWeapon) const
{
	if (Weapon)
	{
		AmmoWeapon = Weapon->Get_Current_Ammo_Weapon();
		return true;
	}
	return false;
}

void UTDWeaponComponent::SpawnWeapon() 
{
	Weapon = GetWorld()->SpawnActor<ATDBaseWeapon>(WeaponClass);
	if (Weapon)
	{
		const auto Character = Cast<ACharacter>(GetOwner());
		if (Character)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "weapon_r");
		}
	}
}

