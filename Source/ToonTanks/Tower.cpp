// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Math/Quat.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsTankInRange())
	{
		//RotateTurret(Tank->GetActorLocation());
		LerpTowerRotation(DeltaTime);
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	CurrentRotationYaw = GetActorRotation().Yaw;
	GetWorldTimerManager().SetTimer(FireRatetTimeHandler, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (Tank == nullptr) return;

	if(Tank->bIsAlive)
	{
		if (IsTankInRange())
		{
			Fire();
		}
	}
}

bool ATower::IsTankInRange()
{
	float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	if (Distance <= FireRange)
	{
		return true;
	}
	return false;
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::LerpTowerRotation(float DeltaTime)
{
	FQuat TowerRotation(TurretMesh->GetRelativeRotation());
	FVector RequiredVector = Tank->GetActorLocation() - this->GetActorLocation();
	FRotator RequiredRotation = FRotator(0.f, RequiredVector.Rotation().Yaw, 0.f);
	FQuat TargetRotation(RequiredRotation);
	TurretMesh->SetWorldRotation(FQuat::Slerp(TowerRotation, TargetRotation, TurnRate * DeltaTime));
}