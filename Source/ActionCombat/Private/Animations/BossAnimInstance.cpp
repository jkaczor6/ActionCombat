#include "Animations/BossAnimInstance.h"

void UBossAnimInstance::UpdateSpeed()
{
	APawn* PawnRef{ TryGetPawnOwner() };
	if (!PawnRef) { return; }
	
	FVector Velocity{ PawnRef->GetVelocity() };
	CurrentSpeed = static_cast<float>(Velocity.Length());
}
