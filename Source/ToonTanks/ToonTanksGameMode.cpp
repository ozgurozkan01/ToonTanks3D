// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "EnemyTower.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	LivedTowerAmount = GetTowerAmount();
	
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}

	else if (AEnemyTower* Tower = Cast<AEnemyTower>(DeadActor))
	{
		Tower->HandleDestruction();
		LivedTowerAmount--;

		if (LivedTowerAmount == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		
		FTimerDelegate  PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true);

		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			3,
			false);
	}
}

int32 AToonTanksGameMode::GetTowerAmount()
{
	TArray<AActor*> TowersAmount;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemyTower::StaticClass(), TowersAmount);

	return TowersAmount.Num();
}
