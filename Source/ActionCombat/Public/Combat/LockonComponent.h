#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockonComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API ULockonComponent : public UActorComponent
{
	GENERATED_BODY()
	
	ACharacter* OwnerRef;
	APlayerController* Controller;
	class UCharacterMovementComponent* MovementComp;
	class USpringArmComponent* SpringArmComp;
	
public:	
	ULockonComponent();
	
	AActor* CurrentTargetActor;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void StartLockon(float Radius = 750.f);
	
	void EndLockon();
	
	UFUNCTION(BlueprintCallable)
	void ToggleLockon(float Radius = 750.f);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
