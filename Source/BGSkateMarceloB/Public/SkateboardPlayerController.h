#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SkateboardPlayerController.generated.h"

UCLASS()
class BGSKATEMARCELOB_API ASkateboardPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

	void MoveForward(float Value);
	virtual void AddYawInput(float Value) override;
	void Jump();

	bool bIsMovingForward;
};
