// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// forward declaration
class UTankBarrel;

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent(); // contructor
	void AimAt(FVector AimLocation, float LaunchSpeed);
	void SetBarrelReference(UTankBarrel * BarrelToSet);
private:	
	UTankBarrel * Barrel = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	
};