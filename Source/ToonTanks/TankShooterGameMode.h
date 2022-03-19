// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankShooterGameMode.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATankShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	
	class ATank* Tank;
	class ATankShooterPlayerController* TankPlayerController;
	float StartDelay = 3.f;
	int32 AllTowers;
	int32 GetAllTowers();
	void HandleGameStart();
};
