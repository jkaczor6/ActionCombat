#include "Animations/PlayerAnimInstance.h"

void UPlayerAnimInstance::UpdateVelocity()
{
	APawn* PawnRef{ TryGetPawnOwner() };
	if (!PawnRef) { return; }
	
	FVector Velocity{ PawnRef->GetVelocity() };
	CurrentVelocity = static_cast<float>(Velocity.Length());
}
