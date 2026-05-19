#include "Characters/AI/BTT_RangeAttack.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EEnemyState.h"

EBTNodeResult::Type UBTT_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* CharacterRef{ OwnerComp.GetAIOwner()->GetPawn<ACharacter>() };
	
	if (!CharacterRef) { return EBTNodeResult::Failed; }
	
	float Distance{ OwnerComp.GetBlackboardComponent()->GetValueAsFloat("Distance") };
	if (Distance < MeleeRange)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("CurrentState", EEnemyState::Melee);
		AbortTask(OwnerComp, NodeMemory);
		
		return EBTNodeResult::Aborted;
	}
	
	CharacterRef->PlayAnimMontage(AnimMontage);
	
	double RandomValue{ UKismetMathLibrary::RandomFloat() };
	if (RandomValue > Threshold)
	{
		Threshold = 0.9;
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), EEnemyState::Charge);
	}
	else
	{
		Threshold -= 0.1;
	}
	
	return EBTNodeResult::Succeeded;
}
