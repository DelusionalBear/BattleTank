#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent) { FoundAimingComponent(AimingComponent); }
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() const
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!AimingComponent) { return; }

	FHitResult HitResult;
	if (TraceHitLocation(HitResult))
	{
		AimingComponent->AimAt(HitResult.Location);
	}
	return;
}

// Traces world space coordinates for crosshair
bool ATankPlayerController::TraceHitLocation(FHitResult& HitResult) const
{
	// find crosshair position for current viewport size
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	
	// get world space coordinates within FHitResult and return true. Returns false if no object has been hit.
	// If we were looking at skybox for example.
	if (GetHitResultAtScreenPosition(ScreenLocation, ECollisionChannel::ECC_Visibility, false, HitResult)) { return true; }
	else { return false; }
}