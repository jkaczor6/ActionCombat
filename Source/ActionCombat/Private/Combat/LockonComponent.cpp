#include "Combat/LockonComponent.h"

ULockonComponent::ULockonComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

