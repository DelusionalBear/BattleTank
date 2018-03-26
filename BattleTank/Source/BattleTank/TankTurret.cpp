// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	auto RotationChange = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0.0f, Rotation, 0.0f));
	// UE_LOG(LogTemp, Warning, TEXT("Rotation change is: %f"), RotationChange);
}


