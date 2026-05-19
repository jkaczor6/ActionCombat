#include "Characters/BossCharacter.h"
#include "Characters/StatsComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/CombatComponent.h"
#include "Characters/MainCharacter.h"
#include "Components/CapsuleComponent.h"

ABossCharacter::ABossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	ControllerRef = GetController<AAIController>();
	
	BlackboardComp = ControllerRef->GetBlackboardComponent();
	
	BlackboardComp->SetValueAsEnum(TEXT("CurrentState"), InitialState);
	
	GetWorld()->GetFirstPlayerController()
		->GetPawn<AMainCharacter>()
		->StatsComp
		->OnZeroHealthDelegate
		.AddDynamic(this, &ABossCharacter::HandlePlayerDeath);
}

void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABossCharacter::DetectPawn(APawn* DetectedPawn, APawn* PawnToCheckFor)
{
	EEnemyState CurrentState{
		static_cast<EEnemyState>(BlackboardComp->GetValueAsEnum(TEXT("CurrentState")))
	};
	
	if (DetectedPawn != PawnToCheckFor || CurrentState != EEnemyState::Idle) { return; }
	
	BlackboardComp->SetValueAsEnum(TEXT("CurrentState"), EEnemyState::Range);
}

float ABossCharacter::GetDamage()
{
	return StatsComp->Stats[EStats::Strength];
}

void ABossCharacter::Attack()
{
	CombatComp->RandomAttack();
}

float ABossCharacter::GetAnimDuration()
{
	return CombatComp->AnimDuration;
}

float ABossCharacter::GetMeleeRange()
{
	return StatsComp->Stats[EStats::MeleeRange];
}

void ABossCharacter::HandlePlayerDeath()
{
	BlackboardComp->SetValueAsEnum("CurrentState", EEnemyState::GameOver);
}

void ABossCharacter::HandleDeath()
{
	float AnimDuration{ PlayAnimMontage(DeathAnimMontage) };
	
	ControllerRef->BrainComponent->StopLogic("defeated");
	
	FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FTimerHandle DestroyTimerHandle;
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ABossCharacter::FinishDeathAnimation, AnimDuration, false);
	
}

void ABossCharacter::FinishDeathAnimation()
{
	Destroy();	
}
