#include "Characters/AI/BTT_ChargeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Animations/BossAnimInstance.h"

EBTNodeResult::Type UBTT_ChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ControllerRef = OwnerComp.GetAIOwner();
	CharacterRef = ControllerRef->GetCharacter();
	BossAnim = Cast<UBossAnimInstance>( CharacterRef->GetMesh()->GetAnimInstance() );
	if (!BossAnim) { return EBTNodeResult::Failed; }
	
	BossAnim->bIsCharging = true;
	
	return EBTNodeResult::InProgress;
}
