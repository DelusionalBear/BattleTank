#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack(); // constructor

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction);

	void ApplySidewaysForce();

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	void DriveTrack();

	float CurrentThrottle = 0.0f;

	// Max force per track 
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.0f;
 };