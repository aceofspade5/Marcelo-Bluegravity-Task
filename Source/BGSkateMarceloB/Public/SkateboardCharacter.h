#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkateboardCharacter.generated.h"

UCLASS()
class BGSKATEMARCELOB_API ASkateboardCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASkateboardCharacter();

protected:
    virtual void BeginPlay() override;

public:	
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


    void Move(const struct FInputActionValue& Value);
    void Look(const struct FInputActionValue& Value);


    void StopMove();

private:

    float CurrentSpeed;
    float MaxSpeed;
    float MinSpeed;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    bool bIsMovingForward;

   
    void MaintainForwardMovement(float DeltaTime);
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FollowCamera;

    // Enhanced Input Actions
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* JumpAction;
};
