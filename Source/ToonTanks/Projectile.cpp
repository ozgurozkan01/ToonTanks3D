// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // We have changed this as false because we r not gonna use it.

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Comp"));
	ProjectileMovementComponent->InitialSpeed = 250.f;
	ProjectileMovementComponent->MaxSpeed = 400.f;

	SmokeTrailParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail Particle Effect"));
	SmokeTrailParticleEffect->SetupAttachment(RootComponent);

	ShootingSmokeParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shooting Smoke Particle Effect"));
	ShootingSmokeParticleEffect->SetupAttachment(RootComponent); 
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (LaunchSoundEffect)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSoundEffect, GetActorLocation());
	}

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();

	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}
	
	AController* MyOwnerInstigator = GetOwner()->GetInstigatorController();
	
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, UDamageType::StaticClass());

		if (HitParticleEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticleEffect, GetActorLocation(), GetActorRotation());
		}

		if (HitSoundEffect)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSoundEffect, GetActorLocation());
		}

		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
	Destroy();
}
