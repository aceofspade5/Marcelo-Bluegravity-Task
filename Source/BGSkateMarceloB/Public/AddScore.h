#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AddScore.generated.h"

UCLASS()
class BGSKATEMARCELOB_API AAddScore : public AActor
{
	GENERATED_BODY()
    
public:    
	AAddScore();

protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ResetOverlap();

	FTimerHandle OverlapTimerHandle;
	bool bCanOverlap;
};