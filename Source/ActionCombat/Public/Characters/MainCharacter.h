#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
#include "MainCharacter.generated.h"

UCLASS()
class ACTIONCOMBAT_API AMainCharacter : public ACharacter, public IMainPlayer
{
	GENERATED_BODY()

public:
	AMainCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	class UPlayerAnimInstance* PlayerAnim;
	
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
