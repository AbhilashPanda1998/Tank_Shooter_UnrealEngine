// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class ATank* Tank;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 300.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float TurnRate = 7.f;
	float CurrentRotationYaw;
	float FireRate = 2.f;
	FTimerHandle FireRatetTimeHandler;
	void CheckFireCondition();
	void LerpTowerRotation(float DeltaTime);
	bool IsTankInRange();
};
