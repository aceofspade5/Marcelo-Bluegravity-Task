#include "SkateboardGameMode.h"
#include "SkateboardHUD.h"

ASkateboardGameMode::ASkateboardGameMode()
{
	PlayerScore = 0;
	HUDClass = ASkateboardHUD::StaticClass();
}

void ASkateboardGameMode::AddScore(int32 ScoreAmount)
{
	PlayerScore += ScoreAmount;
	UE_LOG(LogTemp, Warning, TEXT("Player Score: %d"), PlayerScore);
}