#include "Characters/MainCharacter.h"
#include "Animations/PlayerAnimInstance.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (!PlayerAnim) { return; }
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

