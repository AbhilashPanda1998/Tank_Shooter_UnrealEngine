// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Component"));
	SpringComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringComponent);
}
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
	PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
}
 
// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		RotateTurret(GetHitPoint());
	}
}

void ATank::Move(float Value)
{
	FVector TestVector = FVector::ZeroVector;
	float ValueNeeded = UGameplayStatics::GetWorldDeltaSeconds(this) * Speed * Value;
	TestVector.X = ValueNeeded;
	AddActorLocalOffset(TestVector, true);
}

void ATank::Turn(float Value)
{
	FRotator TestRotator = FRotator::ZeroRotator;
	float ValueNeeded = UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate * Value;
	TestRotator.Yaw = ValueNeeded;
	AddActorLocalRotation(TestRotator, true);
}

FVector ATank::GetHitPoint()
{
	FHitResult HitResult;

	PlayerControllerRef->GetHitResultUnderCursor(
		ECollisionChannel::ECC_Visibility,
		false,
		HitResult);

	return HitResult.ImpactPoint;
};
