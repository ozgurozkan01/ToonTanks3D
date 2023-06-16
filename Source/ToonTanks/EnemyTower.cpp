// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void AEnemyTower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (IsInFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void AEnemyTower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();

	// We need to store a Tank that in the game. Cause we r gonna use tank location to calculate distance between tower.
	// this here , one side is child (ATank) and the other side is parent (APawn)
	// So we cannot attach these to variables each other
	// We need to use Cast<>();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyTower::CheckFireCondition, FireRate, true);
}

void AEnemyTower::CheckFireCondition()
{
	if (Tank == nullptr)
	{
		return;
	}
	
	if(IsInFireRange() && Tank->bIsAlive)
	{
		Fire();
	}
}

bool AEnemyTower::IsInFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}

