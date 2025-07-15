// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TDDefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TDHealthComponent.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "Weapon\TDWeaponComponent.h"

// Sets default values
ATDDefaultCharacter::ATDDefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	springArmComponent->SetupAttachment(GetRootComponent());
	springArmComponent->SetUsingAbsoluteRotation(true);
	springArmComponent->TargetArmLength = ArmLength;
	springArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
	springArmComponent->bDoCollisionTest = false;
	springArmComponent->bEnableCameraLag = true;

	cameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	cameraComponent->SetupAttachment(springArmComponent);
	cameraComponent->SetFieldOfView(FOV);
	cameraComponent->bUsePawnControlRotation = false;
	
	healthComponent = CreateDefaultSubobject<UTDHealthComponent>("Health_Component");
	weaponComponent = CreateDefaultSubobject<UTDWeaponComponent>("Weapon");

}

// Called when the game starts or when spawned
void ATDDefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (cursorMaterial)
	{
		currentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), cursorMaterial, cursorSize, FVector(0));
	}
	healthComponent->OnDeath.AddUObject(this, &ATDDefaultCharacter::OnDeath);
	OnHealthChanged(healthComponent->Get_Health());
	healthComponent->OnHealthChanged.AddUObject(this, &ATDDefaultCharacter::OnHealthChanged);
	
}

// Called every frame
void ATDDefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (SprintRequest && !canSprint)
	{
		canSprint = true;
		currentSpeed = GetCharacterMovement()->MaxWalkSpeed;
		GetCharacterMovement()->MaxWalkSpeed = maxSpeedSprint;
	}
	if (!SprintRequest && canSprint)
	{
		canSprint = false;
		GetCharacterMovement()->MaxWalkSpeed = currentSpeed;
	}
	if (!(healthComponent->IsDead()))
	{
		RotationPlayerOnCursor();
	}
	

}

// Called to bind functionality to input
void ATDDefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATDDefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATDDefaultCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Closer", this, &ATDDefaultCharacter::CloseCamera);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ATDDefaultCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ATDDefaultCharacter::StopSprint);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, weaponComponent, &UTDWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, weaponComponent, &UTDWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, weaponComponent, &UTDWeaponComponent::Reload);


}
void ATDDefaultCharacter::OnHealthChanged(float NewHealth) {
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"), NewHealth));
}
void ATDDefaultCharacter::RotationPlayerOnCursor() {
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
		if (currentCursor)
		{

			currentCursor->SetWorldLocation(ResultHit.Location);
		}
	}
}
void ATDDefaultCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}
void ATDDefaultCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ATDDefaultCharacter::CloseCamera(float Value)
{
	if (FMath::Abs(Value) > 20)
	{
		return;
	}
	if (springArmComponent->TargetArmLength >= ArmMax && Value == 20)
	{
		return;
	}
	else if (springArmComponent->TargetArmLength <= ArmMin+100 && Value == -20)
	{
		return;
	}
	else
	{
		springArmComponent->TargetArmLength += Value;
	}
	
	
}

void ATDDefaultCharacter::StartSprint() 
{
	SprintRequest = true;
}

void ATDDefaultCharacter::StopSprint() { 
	SprintRequest = false;
}

void ATDDefaultCharacter::OnDeath()
{
	currentCursor->DestroyRenderState_Concurrent();
	PlayAnimMontage(DeathMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.f);
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}