// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.1/Engine/Platforms/Hololens/Source/Runtime/Core/Public/Microsoft/AllowMicrosoftPlatformTypesPrivate.h"
#include "EnemyTower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AEnemyTower : public ABasePawn
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;
	
	void HandleDestruction();
	
protected:
	virtual void BeginPlay() override;
private:
	// Variables is used as component declare with pointer. 
	// We need to add header or use forward declaration
	// In this states using forward declaration is better than adding header for performans. 
	class ATank* Tank;

	UPROPERTY(EditAnywhere, Category="Combat")
	float FireRange = 300.f;


	FTimerHandle TimerHandle;
	float FireRate = 3.f;

	void CheckFireCondition();
	bool IsInFireRange();
};
