#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MeleeAttack.generated.h"

UCLASS()
class ACTIONCOMBAT_API UBTT_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float AttackRadius{ 200.f };
	UPROPERTY(EditAnywhere)
	float AcceptableRadius{ 100.f };	
protected:
	virtual void TickTask ( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds ) override;
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
