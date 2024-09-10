// SkateboardHUD.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SkateboardHUD.generated.h"

UCLASS()
class BGSKATEMARCELOB_API ASkateboardHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

	class ASkateboardGameMode* GameMode;

protected:
	virtual void BeginPlay() override;
};
