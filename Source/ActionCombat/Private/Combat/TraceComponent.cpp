#include "Combat/TraceComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/Fighter.h"
#include "Engine/DamageEvents.h"

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

	if (!bIsAttacking) { return; }
	
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
	if (bDebugMode)
	{
		FVector CenterPoint{ UKismetMathLibrary::VLerp(StartSocketLocation, EndSocketLocation, 0.5f)};
		
		UKismetSystemLibrary::DrawDebugBox(
			GetWorld(),
			CenterPoint,
			Box.GetExtent(),
			bHasFoundTargets ? FLinearColor::Green : FLinearColor::Red,
			ShapeRotation.Rotator(),
			1.f,
			2.f
		);
	}
	if (!bHasFoundTargets) {return;}
	
	float CharacterDamage{0.f};
	
	IFighter* FighterRef{ Cast<IFighter>(GetOwner()) };
	if (!FighterRef) { return; }
	
	CharacterDamage = FighterRef->GetDamage();
	FDamageEvent TargetAttacketEvent;	
	
	for (const FHitResult& Hit: OutResults)
	{
		AActor* TargetActor{ Hit.GetActor() };
		if (TargetsToIgnore.Contains(TargetActor)) { continue; }
		TargetActor->TakeDamage(
			CharacterDamage,
			TargetAttacketEvent,
			GetOwner()->GetInstigatorController(),
			GetOwner()
		);
		TargetsToIgnore.AddUnique(TargetActor);
	}
}

void UTraceComponent::HandleResetAttack()
{
	TargetsToIgnore.Empty();
}

