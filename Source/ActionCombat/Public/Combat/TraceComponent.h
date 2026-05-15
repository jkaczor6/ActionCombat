#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

	USkeletalMeshComponent* SkeletalComp;
	
	UPROPERTY(EditAnywhere)
	FName Start;
	UPROPERTY(EditAnywhere)
	FName End;
	UPROPERTY(EditAnywhere)
	FName Rotation;
	
	UPROPERTY(EditAnywhere)
	double BoxLength{30.0};
	
	UPROPERTY(EditAnywhere)
	bool bDebugMode{ false };
public:	
	UTraceComponent();

protected:
	virtual void BeginPlay() override;

	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
