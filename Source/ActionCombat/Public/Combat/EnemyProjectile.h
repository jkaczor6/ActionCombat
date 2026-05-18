#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.generated.h"

UCLASS()
class ACTIONCOMBAT_API AEnemyProjectile : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* HitTemplate;
public:	
	AEnemyProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void HandleBeginOverlap(AActor* OtherActor);
	
	UFUNCTION()
	void DestroyProjectile();
};
