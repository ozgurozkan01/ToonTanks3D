// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm);

	DeltaLocation = FVector::ZeroVector;

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(
			ECC_Visibility,
			false,
			HitResult);

		DrawDebugSphere(
		GetWorld(),
		HitResult.ImpactPoint,
		10,
	10,
		FColor::Blue);

		
		/*FVector WorldLocation;
		FVector WorldDirection;
		PlayerControllerRef->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

		FVector TurnOrigin = TurretMesh->GetComponentLocation();
		FVector MouseWorldLocation = FMath::LinePlaneIntersection(
			WorldLocation,
			WorldLocation + WorldDirection,
			TurnOrigin,
			FVector::UpVector);


		DrawDebugSphere(
		GetWorld(),
		MouseWorldLocation,
		10,
		10,
		FColor::Red);*/

		//UE_LOG(LogTemp, Warning, TEXT("%s"), *MouseWorldLocation.ToCompactString());
		
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);
	bIsAlive = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value)
{
	DeltaLocation.X = Value * GetWorld()->GetDeltaSeconds() * MovementSpeed;
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	if (DeltaLocation.X == 0)
	{return;}

	if (DeltaLocation.X < 0)
	{
		DirectionMultiplier = -1;
	}

	else
	{
		DirectionMultiplier = 1;
	}
	
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * GetWorld()->GetDeltaSeconds() * TurnRate * DirectionMultiplier;
	AddActorLocalRotation(DeltaRotation, true);
}	
