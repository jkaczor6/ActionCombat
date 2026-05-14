#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class ACTIONCOMBAT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentSpeed{ 0.f };
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentDirection{ 0.f };
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInCombat{ false };
	
	UFUNCTION(BlueprintCallable)
	void UpdateSpeed();
	UFUNCTION(BlueprintCallable)
	void UpdateDirection();
public:
	UFUNCTION(BlueprintCallable)
	void HandleUpdatedTarget(AActor* NewTargetActorRef);
};
