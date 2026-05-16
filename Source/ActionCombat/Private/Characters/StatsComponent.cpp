#include "Characters/StatsComponent.h"
#include "Kismet/KismetMathLibrary.h"

UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UStatsComponent::ReduceHealth(float Damage)
{
	if (Stats[EStats::Health] <= 0) { return; }
	
	Stats[EStats::Health] -= Damage;
	
	Stats[EStats::Health] = UKismetMathLibrary::FClamp(Stats[EStats::Health], 0, Stats[EStats::MaxHealth]);
}

