#include "Characters/AI/BTT_RangeAttack.h"

EBTNodeResult::Type UBTT_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("Task succeeded"));
	
	return EBTNodeResult::Succeeded;
}
