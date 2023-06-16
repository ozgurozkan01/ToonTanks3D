// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystem;
class USoundBase;
class UCameraShakeBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	UStaticMeshComponent* ProjectileMesh;
	
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent * ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category="Combat")
	UParticleSystem* HitParticleEffect;

	UPROPERTY(VisibleAnywhere, Category="Combat")
	UParticleSystemComponent* SmokeTrailParticleEffect;

	UPROPERTY(VisibleAnywhere, Category="Combat")
	UParticleSystemComponent* ShootingSmokeParticleEffect;

	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* LaunchSoundEffect;

	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* HitSoundEffect;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
