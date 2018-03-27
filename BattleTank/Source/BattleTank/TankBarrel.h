// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/*
 This fucking nonsense exist solely for the purpose of having nice method called "Elevate"
 which operates barrel of our tank. I mean WTF??? Turret and barrel are merely glorified
 UI that represents state of our tank in 3d. We don't need this kind of convoluted mess.
 Angle restrictions for barrel, along with methods that rotate turret and elevate barrel
 could be easily placed inside Tank.h/.cpp and operate on standard UStaticMeshComponent we
 used to build our tank in the Blueprint.

 If for some reason you're reading this and you want to be in game development, please
 do yourself a favor, stay away from various gamedev 'entrepreneurs'. Buy yourself a good
 book on C++ and Google through Unreal Documentation. Point is, if you're any good to make
 it through this course you WILL have to do it anyway.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationDegrees = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 40.0f;
};
