#include "Combat/LockonComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"

ULockonComponent::ULockonComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerRef = GetOwner<ACharacter>();
	Controller = GetWorld()->GetFirstPlayerController();
	MovementComp = OwnerRef->GetCharacterMovement();
	SpringArmComp = OwnerRef->FindComponentByClass<USpringArmComponent>();
}

void ULockonComponent::StartLockon(float Radius)
{
	FHitResult OutResult;
	FVector CurrentLocation{ OwnerRef->GetActorLocation() };
	FCollisionShape Sphere{ FCollisionShape::MakeSphere(Radius) };
	FCollisionQueryParams IgnoreParams{
		FName{TEXT("Ignore Collision Params")},
		false,
		OwnerRef
	};
	
	bool bHasFoundTarget{GetWorld()->SweepSingleByChannel(
		OutResult,
		CurrentLocation,
		CurrentLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		Sphere,
		IgnoreParams
	)};
	
	if (!bHasFoundTarget) {return; }
	
	CurrentTargetActor = OutResult.GetActor();
	
	Controller->SetIgnoreLookInput(true);
	MovementComp->bOrientRotationToMovement = false;
	MovementComp->bUseControllerDesiredRotation = true;
	
	SpringArmComp->TargetOffset = FVector{0.f,0.f,100.f};
}

void ULockonComponent::EndLockon()
{
	CurrentTargetActor = nullptr;
	
	Controller->ResetIgnoreLookInput();
	MovementComp->bOrientRotationToMovement = true;
	MovementComp->bUseControllerDesiredRotation = false;
	
	SpringArmComp->TargetOffset = FVector::ZeroVector;
}

void ULockonComponent::ToggleLockon(float Radius)
{
	if (!CurrentTargetActor) {StartLockon(Radius);} else {EndLockon();};
}


void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CurrentTargetActor){ return; }
	
	FVector CurrentLocation{OwnerRef->GetActorLocation()};
	FVector TargetLocation{CurrentTargetActor->GetActorLocation()};
	
	TargetLocation.Z -= 125;
	
	FRotator NewRotation{UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation)};
	Controller->SetControlRotation(NewRotation);
}

