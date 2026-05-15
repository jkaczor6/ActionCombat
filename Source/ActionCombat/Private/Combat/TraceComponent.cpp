#include "Combat/TraceComponent.h"

UTraceComponent::UTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	SkeletalComp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
}


void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector StartSocketLocation{ SkeletalComp->GetSocketLocation(Start) };
	FVector EndSocketLocation{ SkeletalComp->GetSocketLocation(End) };
	FQuat ShapeRotation{ SkeletalComp->GetSocketQuaternion(Rotation) };
	
	double WeaponDistance{FVector::Distance(StartSocketLocation, EndSocketLocation)};
	FVector BoxDimensions{BoxLength, BoxLength, WeaponDistance};
	FCollisionShape Box{FCollisionShape::MakeBox(BoxDimensions / 2)};
	FCollisionQueryParams IgnoreParams{
		FName{TEXT("Ignore Params")},
		false,
		GetOwner()
	};
	
	TArray<FHitResult> OutResults;
	bool bHasFoundTargets = GetWorld()->SweepMultiByChannel(
		OutResults,
		StartSocketLocation,
		EndSocketLocation,
		ShapeRotation,
		ECC_GameTraceChannel1,
		Box,
		IgnoreParams
	);
	if (bHasFoundTargets)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Target Found!"));
	}
}

