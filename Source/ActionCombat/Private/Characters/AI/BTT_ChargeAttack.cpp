#include "Characters/AI/BTT_ChargeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Animations/BossAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"


UBTT_ChargeAttack::UBTT_ChargeAttack()
{
	bNotifyTick = true;
}

void UBTT_ChargeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	bool bIsReadyToCharge = OwnerComp.GetBlackboardComponent()->GetValueAsBool("IsReadyToCharge");
	
	if (bIsReadyToCharge)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsReadyToCharge", false);
		ChargeAtPlayer();
	}
}

EBTNodeResult::Type UBTT_ChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ControllerRef = OwnerComp.GetAIOwner();
	CharacterRef = ControllerRef->GetCharacter();
	BossAnim = Cast<UBossAnimInstance>( CharacterRef->GetMesh()->GetAnimInstance() );
	if (!BossAnim) { return EBTNodeResult::Failed; }
	
	BossAnim->bIsCharging = true;
	
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsReadyToCharge", false);
	
	return EBTNodeResult::InProgress;
}

void UBTT_ChargeAttack::ChargeAtPlayer()
{
	APawn* PlayerRef{ GetWorld()->GetFirstPlayerController()->GetPawn() };
	FVector PlayerLocation{ PlayerRef->GetActorLocation() };
	
	FAIMoveRequest MoveRequest{ PlayerLocation };
	MoveRequest.SetUsePathfinding(true);
	MoveRequest.SetAcceptanceRadius(AcceptableRadius);
	
	ControllerRef->MoveTo(MoveRequest);
	ControllerRef->SetFocus(PlayerRef);
}
