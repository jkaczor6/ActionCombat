#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockonComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdatedTargetSignature,
	ULockonComponent, OnUpdatedTargetDelegate,
	AActor*, NewTargetActorRef
	);

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
	
	UPROPERTY(BlueprintAssignable)
	FOnUpdatedTargetSignature OnUpdatedTargetDelegate;
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void StartLockon(float Radius = 750.f);
	
	UFUNCTION(BlueprintCallable)
	void ToggleLockon(float Radius = 750.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double BreakDistance{ 1000.0 };

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void EndLockon();
};
