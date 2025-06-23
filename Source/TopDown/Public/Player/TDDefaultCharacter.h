// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDDefaultCharacter.generated.h"




	class UCameraComponent;
	class USpringArmComponent;

UCLASS()
class TOPDOWN_API ATDDefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATDDefaultCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* cameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* springArmComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float ArmMax = 1600.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float ArmMin = 600.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	UDecalComponent* currentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* cursorMaterial = nullptr;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector cursorSize = FVector(20.0f, 40.0f, 40.0f);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float YRotation = -75.0f;
	float ArmLength = 1400.0f;
	float FOV = 55.0f;
	

	void MoveForward(float Value);
	void MoveRight(float Value);
	void CloseCamera(float Value);

};
