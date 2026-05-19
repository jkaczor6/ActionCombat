#include "Characters/AI/BTT_MeleeAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

UBTT_MeleeAttack::UBTT_MeleeAttack()
{
	bNotifyTick = true;
	
	MoveDelegate.BindUFunction(this, "FinishAttackTask");
}

void UBTT_MeleeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!bIsFinished) { return; }
	
	OwnerComp.GetAIOwner()->ReceiveMoveCompleted.Remove(MoveDelegate);
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

EBTNodeResult::Type UBTT_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bIsFinished = false;
	
	float Distance{ OwnerComp.GetBlackboardComponent()->GetValueAsFloat("Distance") };
	if (Distance > AttackRadius)
	{
		APawn* PlayerRef { GetWorld()->GetFirstPlayerController()->GetPawn() };
		FAIMoveRequest MoveRequest{ PlayerRef };
		MoveRequest.SetUsePathfinding(true);
		MoveRequest.SetAcceptanceRadius(AcceptableRadius);
		
		OwnerComp.GetAIOwner()->ReceiveMoveCompleted.AddUnique(MoveDelegate);
		
		OwnerComp.GetAIOwner()->MoveTo(MoveRequest);
		OwnerComp.GetAIOwner()->SetFocus(PlayerRef);
	}
	
	return EBTNodeResult::InProgress;
}

void UBTT_MeleeAttack::FinishAttackTask()
{
	bIsFinished = true;
}
