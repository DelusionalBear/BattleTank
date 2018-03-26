// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

// Forward declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector AimLocation);
	
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel * BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret * TurretToSet);

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000.0f;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ReloadTimeInSeconds = 3.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent *TankAimingComponent = nullptr;

private:
	// local barrel reference for spawning projectile. OMFG.
	// we could just have this one variable here as UStaticMesh component
	// for barrel mesh and firing and methods to elevate it and do whatever
	// we like. Instead he created another class that does absolutely NOTHING,
	// other than having one single method.. and now this thing is still needed
	// here for firing. This is so retarded...
	UTankBarrel * Barrel = nullptr;

	double LastFireTime = 0;
};
