#include "Combat/EnemyProjectile.h"

AEnemyProjectile::AEnemyProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyProjectile::HandleBeginOverlap(AActor* OtherActor)
{
	APawn* PawnRef{ Cast<APawn>(OtherActor) };
	if (!PawnRef->IsPlayerControlled()) { return; }
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlapped with Player!"));
}

