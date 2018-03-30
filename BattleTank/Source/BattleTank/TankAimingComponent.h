#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

// forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent(); // contructor

	virtual void BeginPlay() override;

	bool IsBarrelMoving();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTurret *TurretToSet, UTankBarrel *BarrelToSet);
	void AimAt(FVector AimLocation);

	UPROPERTY(BlueprintReadOnly, Category = "State")
	int ShotsLeft = 5;
	
	UPROPERTY(BlueprintReadOnly, Category = "State")
	float LastFireTimeDelta = ReloadTimeInSeconds;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	UTankTurret *Turret = nullptr;
	UTankBarrel *Barrel = nullptr;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void MoveBarrelTowards(FVector AimDir);
	double LastFireTime = 0;
	FVector AimDirection;
};