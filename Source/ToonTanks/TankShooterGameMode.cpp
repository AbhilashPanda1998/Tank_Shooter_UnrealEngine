// Fill out your copyright notice in the Description page of Project Settings.


#include "TankShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "TankShooterPlayerController.h"
#include "TimerManager.h"

void ATankShooterGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (TankPlayerController)
		{
			TankPlayerController->SetPlayerEnabledState(false);
            GameOver(false);
		}
	}

	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
        AllTowers--;
        if (AllTowers == 0)
        {
            GameOver(true);
        }
	}
}

void ATankShooterGameMode::BeginPlay()
{
	Super::BeginPlay(); 
    HandleGameStart();
}

void ATankShooterGameMode::HandleGameStart()
{
    AllTowers = GetAllTowers();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    TankPlayerController = Cast<ATankShooterPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if (TankPlayerController)
    {
        TankPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            TankPlayerController,
            &ATankShooterPlayerController::SetPlayerEnabledState,
            true
        );
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
            PlayerEnableTimerDelegate,
            StartDelay,
            false
        );
    }
}

int ATankShooterGameMode::GetAllTowers()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}
