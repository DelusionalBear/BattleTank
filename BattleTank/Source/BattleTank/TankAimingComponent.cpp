// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::AimAt(FVector AimLocation, float LaunchSpeed)
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
		// UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), Time);
	}
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	if (DeltaRotator.Yaw >= 180.0f) { DeltaRotator.Yaw = DeltaRotator.Yaw - 360.0f; }
	else if (DeltaRotator.Yaw <= -180.0f) { DeltaRotator.Yaw = DeltaRotator.Yaw + 360.0f; }
	/*UE_LOG(LogTemp, Warning, TEXT("Aim Direction Unit Vector: %s"), *AimDirection.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Aim Rotator: %s"), *AimAsRotator.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Barrel Rotator: %s"), *BarrelRotator.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Delta Rotator: %s"), *DeltaRotator.ToString());*/
	Turret->Rotate(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}