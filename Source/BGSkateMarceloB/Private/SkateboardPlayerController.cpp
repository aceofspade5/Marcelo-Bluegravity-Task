#include "SkateboardPlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

void ASkateboardPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ASkateboardPlayerController::MoveForward);
	InputComponent->BindAxis("Turn", this, &ASkateboardPlayerController::AddYawInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ASkateboardPlayerController::Jump);
}

void ASkateboardPlayerController::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		bIsMovingForward = true;
		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn)
		{
			FVector Forward = ControlledPawn->GetActorForwardVector();
			ControlledPawn->AddMovementInput(Forward, Value);
		}
	}
	else
	{
		bIsMovingForward = false;
	}
}

void ASkateboardPlayerController::AddYawInput(float Value)
{
	if (Value != 0.0f)
	{
		GetPawn()->AddControllerYawInput(Value);
	}
}

void ASkateboardPlayerController::Jump()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn);
		if (ControlledCharacter)
		{
			ControlledCharacter->Jump();
		}
	}
}