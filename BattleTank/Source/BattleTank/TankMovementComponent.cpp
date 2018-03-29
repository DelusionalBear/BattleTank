#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto CurrTankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIMoveIntentionVector = MoveVelocity.GetSafeNormal();
	IntendMoveForward(FVector::DotProduct(CurrTankForwardVector, AIMoveIntentionVector));
	IntendTurnRight((FVector::CrossProduct(CurrTankForwardVector, AIMoveIntentionVector)).Z);
}
