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

void UStatsComponent::ReduceHealth(float Amount)
{
	if (Stats[EStats::Health] <= 0) { return; }
	
	Stats[EStats::Health] -= Amount;
	
	Stats[EStats::Health] = UKismetMathLibrary::FClamp(Stats[EStats::Health], 0, Stats[EStats::MaxHealth]);
}

void UStatsComponent::ReduceStamina(float Amount)
{
	if (Stats[EStats::Stamina] <= 0) { return; }
	
	Stats[EStats::Stamina] -= Amount;
	
	Stats[EStats::Stamina] = UKismetMathLibrary::FClamp(Stats[EStats::Stamina], 0, Stats[EStats::MaxStamina]);
}

void UStatsComponent::RegenStamina()
{
	Stats[EStats::Stamina] = UKismetMathLibrary::FInterpTo_Constant(
		Stats[EStats::Stamina],
		Stats[EStats::MaxStamina],
		GetWorld()->DeltaTimeSeconds,
		StaminaRegenRate
	);
}

