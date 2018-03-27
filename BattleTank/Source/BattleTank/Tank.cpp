// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "CoreMinimal.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector AimLocation)
{
	TankAimingComponent->AimAt(AimLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!Barrel) { return; }
	if (!ProjectileBlueprint) { return; }	// blueprint setup keep acting up, for some reason
											// every once in a while it will be nullptr and crash
											// now if tank doesn't fire, just check if it has
											// projectile assigned in the Tank_BP

	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && bIsReloaded)
	{
		const FActorSpawnParameters ProjectileSpawnParams = FActorSpawnParameters();
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile")),
				ProjectileSpawnParams);
				Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}