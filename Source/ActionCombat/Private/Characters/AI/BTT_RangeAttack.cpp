#include "Characters/AI/BTT_RangeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UBTT_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* CharacterRef{ OwnerComp.GetAIOwner()->GetPawn<ACharacter>() };
	
	if (!CharacterRef) { return EBTNodeResult::Failed; }
	
	CharacterRef->PlayAnimMontage(AnimMontage);
	
	return EBTNodeResult::Succeeded;
}
