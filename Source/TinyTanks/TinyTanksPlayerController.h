// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TinyTanksPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TINYTANKS_API ATinyTanksPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	void SetPlayerEnabledState(bool bPlayerEnabled);
};
