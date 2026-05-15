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
}

