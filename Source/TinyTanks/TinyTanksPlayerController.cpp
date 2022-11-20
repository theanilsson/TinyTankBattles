// Fill out your copyright notice in the Description page of Project Settings.


#include "TinyTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void ATinyTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
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
