#include "Characters/AI/BTS_PlayerDistance.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTS_PlayerDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* OwnerRef{ OwnerComp.GetAIOwner() };
	ACharacter* CharacterRef{ OwnerRef->GetCharacter() };
	
	FVector EnemyLocation{ CharacterRef->GetActorLocation() };
	
	APawn* PlayerRef{ GetWorld()->GetFirstPlayerController()->GetPawn() };
	FVector PlayerLocation{ PlayerRef->GetActorLocation() };
	
	float Distance{ static_cast<float>(FVector::Distance(EnemyLocation, PlayerLocation)) };
	
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat("Distance", Distance);
}
