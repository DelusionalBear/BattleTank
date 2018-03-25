// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	/* auto AIControlledTank = GetControlledTank();
	if (!AIControlledTank) { UE_LOG(LogTemp, Error, TEXT("AIController not possessing a tank!")); }
	else { UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *AIControlledTank->GetName()); }

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) { UE_LOG(LogTemp, Error, TEXT("AIController can't find player tank!")); }
	else { UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *PlayerTank->GetName()); } */
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerPawn) { return nullptr; }
	else { return PlayerPawn; }
}