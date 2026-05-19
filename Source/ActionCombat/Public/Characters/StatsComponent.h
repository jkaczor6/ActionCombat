#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/EStats.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnHealthPercentUpdateSignature,
	UStatsComponent, OnHealthPercentUpdateDelegate,
	float, Percentage
);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnStaminaPercentUpdateSignature,
	UStatsComponent, OnStaminaPercentUpdateDelegate,
	float, Percentage
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	double StaminaRegenRate{ 10.0 };
	
	UPROPERTY(VisibleAnywhere)
	bool bCanRegen{ true };
	
	UPROPERTY(EditAnywhere)
	float StaminaDelayDuration{ 2.f };
public:	
	UStatsComponent();

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStats>, float> Stats;
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthPercentUpdateSignature OnHealthPercentUpdateDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnStaminaPercentUpdateSignature OnStaminaPercentUpdateDelegate;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ReduceHealth(float Amount);
	
	UFUNCTION(BlueprintCallable)
	void ReduceStamina(float Amount);
	
	UFUNCTION(BlueprintCallable)
	void RegenStamina();
	
	UFUNCTION()
	void EnableRegen();
	
	UFUNCTION(BlueprintPure)
	float GetStatPercentage(EStats Current, EStats Max);
};
