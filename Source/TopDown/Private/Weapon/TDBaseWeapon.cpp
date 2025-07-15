// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/TDBaseWeapon.h"
#include <Kismet/KismetSystemLibrary.h>
#include <DrawDebugHelpers.h>


DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);
// Sets default values
ATDBaseWeapon::ATDBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	SetRootComponent(meshComponent);
	ChangeClip();

}

// Called when the game starts or when spawned
void ATDBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ATDBaseWeapon::Fire() 
{
	
	Shoot();
	GEngine->AddOnScreenDebugMessage(
		-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Shot")));
}

void ATDBaseWeapon::DecrementBullets()
{
	CurrentAmmoWeapon.Bullets--;
	GEngine->AddOnScreenDebugMessage(
		-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Bullets = %s"), *FString::FromInt(CurrentAmmoWeapon.Bullets)));
	
	if (IsCurrentClipEmpty())
	{
		BulletsEmpty.Broadcast();
	}
}

bool ATDBaseWeapon::IsCurrentClipEmpty() const
{
	return CurrentAmmoWeapon.Bullets == 0;
}

void ATDBaseWeapon::ChangeClip() 
{
	CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets;
}

bool ATDBaseWeapon::IsCurrentBulletsFull() const
{
	return CurrentAmmoWeapon.Bullets == 30;
}

void ATDBaseWeapon::Shoot()
{
	const FTransform SocketTransform = meshComponent->GetSocketTransform("Muzzle");
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 1.0f, 0, 2.0f);
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	if (HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 24, FColor::Red, false, 1.0f);
	}
	DecrementBullets();
}
// Called every frame
void ATDBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

