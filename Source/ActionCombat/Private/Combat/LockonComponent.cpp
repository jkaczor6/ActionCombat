#include "Combat/LockonComponent.h"

ULockonComponent::ULockonComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void ULockonComponent::StartLockon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Lockon Started"));
}


void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

