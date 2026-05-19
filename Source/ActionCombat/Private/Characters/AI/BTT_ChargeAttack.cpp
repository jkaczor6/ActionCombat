#include "Characters/AI/BTT_ChargeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Animations/BossAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EEnemyState.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTT_ChargeAttack::UBTT_ChargeAttack()
{
	bNotifyTick = true;
	
	MoveCompletedDelegate.BindUFunction(this, "HandleMoveCompleted");
}

void UBTT_ChargeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	bool bIsReadyToCharge = OwnerComp.GetBlackboardComponent()->GetValueAsBool("IsReadyToCharge");
	
	if (bIsReadyToCharge)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsReadyToCharge", false);
		ChargeAtPlayer();
	}
	
	if (!bIsFinished) { return; }
	
	ControllerRef->GetBlackboardComponent()->SetValueAsEnum("CurrentState", EEnemyState::Melee);
	
	ControllerRef->ReceiveMoveCompleted.Remove(MoveCompletedDelegate);
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

EBTNodeResult::Type UBTT_ChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ControllerRef = OwnerComp.GetAIOwner();
	CharacterRef = ControllerRef->GetCharacter();
	BossAnim = Cast<UBossAnimInstance>( CharacterRef->GetMesh()->GetAnimInstance() );
	if (!BossAnim) { return EBTNodeResult::Failed; }
	
	BossAnim->bIsCharging = true;
	
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsReadyToCharge", false);
	
	bIsFinished = false;
	
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
	
	ControllerRef->ReceiveMoveCompleted.AddUnique(MoveCompletedDelegate);
	
	OriginalWalkSpeed = CharacterRef->GetCharacterMovement()->MaxWalkSpeed;
	
	CharacterRef->GetCharacterMovement()->MaxWalkSpeed = ChargeWalkSpeed;
}

void UBTT_ChargeAttack::HandleMoveCompleted()
{
	BossAnim->bIsCharging = false;
	
	FTimerHandle AttackTimerHandler;
	
	CharacterRef->GetWorldTimerManager().SetTimer(AttackTimerHandler, this, &UBTT_ChargeAttack::FinishAttackTask, 1.f, false);
	
	CharacterRef->GetCharacterMovement()->MaxWalkSpeed = OriginalWalkSpeed;
}

void UBTT_ChargeAttack::FinishAttackTask()
{
	bIsFinished = true;
}
