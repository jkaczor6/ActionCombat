#include "Characters/PlayerActionsComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerActionsComponent::UPlayerActionsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPlayerActionsComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = GetOwner<ACharacter>();
	MovementComp = CharacterRef->GetCharacterMovement();
	
	if (!CharacterRef->Implements<UMainPlayer>()) { return; }
	
	IPlayerRef = Cast<IMainPlayer>(CharacterRef);
	if (!IPlayerRef) { return; }
}


void UPlayerActionsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerActionsComponent::Sprint()
{
	if (!IPlayerRef->HasEnoughStamina(SprintCost)) { return; }
	
	MovementComp->MaxWalkSpeed = SprintSpeed;
}

void UPlayerActionsComponent::Walk()
{
	MovementComp->MaxWalkSpeed = WalkSpeed;
}

