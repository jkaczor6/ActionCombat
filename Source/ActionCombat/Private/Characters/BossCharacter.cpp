#include "Characters/BossCharacter.h"
#include "Characters/StatsComponent.h"

ABossCharacter::ABossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	if (DetectedPawn != PawnToCheckFor) { return; }
	
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("Detected Player!"));
}
