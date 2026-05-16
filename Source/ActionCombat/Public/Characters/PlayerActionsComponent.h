#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerActionsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UPlayerActionsComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* CharacterRef;
	
	class IMainPlayer* IPlayerRef;
	
	class UCharacterMovementComponent* MovementComp;
	
	UPROPERTY(EditAnywhere)
	float SprintCost{0.1f};
	
	UPROPERTY(EditAnywhere)
	float SprintSpeed{1000.f};
	
	UPROPERTY(EditAnywhere)
	float WalkSpeed{600.f};
public:	
	UPlayerActionsComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Sprint();
	UFUNCTION(BlueprintCallable)
	void Walk();
};
