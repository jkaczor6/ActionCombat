#include "Characters/AI/BTT_ChargeAttack.h"

EBTNodeResult::Type UBTT_ChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Charging at player!"));
	
	return EBTNodeResult::Succeeded;
}
