// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDBaseWeapon.generated.h"
class USkeletalMeshComponent;

DECLARE_MULTICAST_DELEGATE(FBulletsEmpty)

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

UCLASS()
class TOPDOWN_API ATDBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDBaseWeapon();
	void Fire();
	void DecrementBullets();
	bool IsCurrentClipEmpty() const;
	void ChangeClip();
	FAmmoWeapon Get_Current_Ammo_Weapon() const { return CurrentAmmoWeapon; }
	
	float GetSpeedFire() const { return speedFire; }

	bool IsCurrentBulletsFull() const;

	FBulletsEmpty BulletsEmpty;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* meshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon AmmoWeapon{30, 0, true};
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;
	void Shoot();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	float speedFire = 0.2f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 
	
	FAmmoWeapon CurrentAmmoWeapon;

};
