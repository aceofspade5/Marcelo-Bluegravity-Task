#include "AddScore.h"
#include "Components/BoxComponent.h"
#include "SkateboardCharacter.h"
#include "SkateboardGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AAddScore::AAddScore()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(100.0f, 100.0f, 50.0f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAddScore::OnOverlapBegin);

	bCanOverlap = true;
}

void AAddScore::BeginPlay()
{
	Super::BeginPlay();
}

void AAddScore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAddScore::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bCanOverlap && OtherActor && OtherActor != this)
	{
		if (ASkateboardCharacter* SkateboardCharacter = Cast<ASkateboardCharacter>(OtherActor))
		{
			if (ASkateboardGameMode* GameMode = Cast<ASkateboardGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				GameMode->AddScore(10);
				bCanOverlap = false;
				GetWorld()->GetTimerManager().SetTimer(OverlapTimerHandle, this, &AAddScore::ResetOverlap, 1.0f, false);
			}
		}
	}
}

void AAddScore::ResetOverlap()
{
	bCanOverlap = true;
}