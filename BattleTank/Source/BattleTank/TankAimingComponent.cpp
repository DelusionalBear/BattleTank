// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds)
	{
		FiringState = EFiringStatus::Reloading;
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringStatus::Reloading)
	{
		if (!Barrel) { return; }
		if (!ProjectileBlueprint) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
	}
}

void UTankAimingComponent::Initialise(UTankTurret *TurretToSet, UTankBarrel *BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	if (!Barrel) { return; }

	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,			// world context, basically AimingComponent
		LaunchVelocity, // OUT parameter. SuggestProjectileVelocity puts result here
		StartLocation,	// Barrel end.
		AimLocation,	// We get this as parameter for AimAt()
		LaunchSpeed,	// This is blueprint editable property
		false,			// true for HighArc
		0.0f,			// collision radius
		0.0f,			// 0 to not override gravity
		ESuggestProjVelocityTraceOption::DoNotTrace // trace parameters
	);
	if (bHaveAimSolution) 
	{
		MoveBarrelTowards(LaunchVelocity.GetSafeNormal());
		auto Time = GetWorld()->GetTimeSeconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel || !Turret) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	if (DeltaRotator.Yaw >= 180.0f) { DeltaRotator.Yaw = DeltaRotator.Yaw - 360.0f; }
	else if (DeltaRotator.Yaw <= -180.0f) { DeltaRotator.Yaw = DeltaRotator.Yaw + 360.0f; }
	Turret->Rotate(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}