// Fill out your copyright notice in the Description page of Project Settings.


#include "TinyTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "TinyTanksPlayerController.h"
#include "TimerManager.h"

void ATinyTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (TinyTanksPlayerController)
        {
            TinyTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();
        --TargetTurrets;
        if (TargetTurrets == 0)
        {
            GameOver(true);
        }
    }

    FTimerDelegate TimerDel = FTimerDelegate::CreateUObject(this, &ATinyTanksGameMode::BeginPlay);
}

void ATinyTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void ATinyTanksGameMode::HandleGameStart()
{
    TargetTurrets = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    TinyTanksPlayerController = Cast<ATinyTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if (TinyTanksPlayerController)
    {
        TinyTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            TinyTanksPlayerController,
            &ATinyTanksPlayerController::SetPlayerEnabledState,
            true
        );
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
            PlayerEnableTimerDelegate,
            StartDelay,
            false
        );
    }
}

int32 ATinyTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Towers);
    return Towers.Num();
}