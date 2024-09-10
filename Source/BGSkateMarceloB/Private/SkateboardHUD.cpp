// SkateboardHUD.cpp
#include "SkateboardHUD.h"
#include "SkateboardGameMode.h"
#include "Engine/Canvas.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

void ASkateboardHUD::BeginPlay()
{
	Super::BeginPlay();

	// Pega o GameMode atual
	GameMode = Cast<ASkateboardGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ASkateboardHUD::DrawHUD()
{
	Super::DrawHUD();

	if (GameMode)
	{
		FString ScoreText = FString::Printf(TEXT("Score: %d"), GameMode->PlayerScore);

		FLinearColor TextColor = FLinearColor::Green;
		UFont* HUDFont = GEngine->GetMediumFont();

		if (Canvas)
		{
			Canvas->SetDrawColor(FColor::Green);
			Canvas->DrawText(HUDFont, FText::FromString(ScoreText), 50.0f, 50.0f, 2.0f, 2.0f, FFontRenderInfo());
		}
	}
}