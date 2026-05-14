#include "Animations/PlayerAnimInstance.h"

void UPlayerAnimInstance::UpdateVelocity()
{
	APawn* PawnRef{ TryGetPawnOwner() };
	if (!PawnRef) { return; }
	
	FVector Velocity{ PawnRef->GetVelocity() };
	CurrentVelocity = static_cast<float>(Velocity.Length());
}

void UPlayerAnimInstance::UpdateDirection()
{
	APawn* PawnRef{ TryGetPawnOwner() };
	if (!PawnRef) { return; }
	if (!bIsInCombat) { return; }
	CurrentDirection = CalculateDirection(
		PawnRef->GetVelocity(),
		PawnRef->GetActorRotation()
	);
}

void UPlayerAnimInstance::HandleUpdatedTarget(AActor* NewTargetActorRef)
{
	bIsInCombat = IsValid(NewTargetActorRef);
}
