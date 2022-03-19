// Fill out your copyright notice in the Description page of Project Settings.

#include "TankShooterPlayerController.h"
#include "GameFramework/Pawn.h"

void ATankShooterPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if (bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = bPlayerEnabled;
}

