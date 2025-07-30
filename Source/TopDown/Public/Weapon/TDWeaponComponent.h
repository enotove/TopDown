// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "C:\Users\DNS\Desktop\TopDown\Source\TopDown\Public\Weapon\TDBaseWeapon.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDWeaponComponent.generated.h"


class ATDBaseWeapon;
class UAnimMontage;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWN_API UTDWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTDWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void StartFire();
	void StopFire();
	void FireTickon();

	UFUNCTION(BlueprintCallable)
	bool Get_Current_Ammo(FAmmoWeapon& AmmoWeapon) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* ReloadMontage = nullptr;
	bool AnimReloading = false;
	void Reload();
	void InitAnimNotify();
	void OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh);
	bool CanReload() const;
	FTimerHandle FiresTimerHandle;
	UPROPERTY()
	ATDBaseWeapon* Weapon = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ATDBaseWeapon> WeaponClass;
	

	void SpawnWeapon();
	
};
