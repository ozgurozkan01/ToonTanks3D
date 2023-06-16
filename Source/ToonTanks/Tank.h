// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:

	ATank();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction(); // override function -

	// We can make TankPlayerControler public but it is not good practice
	// Creating a function to get variable is better practice
	// And we use const keyword while creating this function
	// Cause we jsut want to get variable not modifying
	APlayerController* GetTankPlayerController() const {return TankPlayerController;} 
	bool bIsAlive = true;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	    
    UPROPERTY(VisibleAnywhere, Category="Components")
	USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, Category="Components")
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float MovementSpeed = 600.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float TurnRate = 200.f;

	FVector DeltaLocation;
	int DirectionMultiplier;
	
	void Move(float Value);
	void Turn(float Value);
	APlayerController* TankPlayerController;

};

