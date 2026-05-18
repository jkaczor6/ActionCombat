#include "Combat/EnemyProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "Interfaces/MainPlayer.h"
#include "GameFramework/ProjectileMovementComponent.h"

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
	
	FindComponentByClass<UParticleSystemComponent>()->SetTemplate(HitTemplate);
	FindComponentByClass<UProjectileMovementComponent>()->StopMovementImmediately();
	
	FTimerHandle DeathTimerHandle{};
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AEnemyProjectile::DestroyProjectile, 0.5f);
	
	FindComponentByClass<USphereComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FDamageEvent ProjectileAttackEvent{};	
	
	PawnRef->TakeDamage(
		ProjectileDamage,
		ProjectileAttackEvent,
		PawnRef->GetController(),
		this
	);
}

void AEnemyProjectile::DestroyProjectile()
{
	Destroy();
}

