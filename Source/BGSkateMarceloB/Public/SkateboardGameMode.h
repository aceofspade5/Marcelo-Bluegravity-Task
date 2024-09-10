// SkateboardGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SkateboardGameMode.generated.h"

UCLASS()
class BGSKATEMARCELOB_API ASkateboardGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASkateboardGameMode();

	UPROPERTY(BlueprintReadOnly, Category = "Score")
	int32 PlayerScore;

	void AddScore(int32 ScoreAmount);
};
