#include "SkateboardCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASkateboardCharacter::ASkateboardCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    bIsMovingForward = false;

    CurrentSpeed = 400.0f;
    MaxSpeed = 1000.0f;
    MinSpeed = 200.0f;
    GetCharacterMovement()->JumpZVelocity = 500.0f;

    bUseControllerRotationPitch = true;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = false;
}

void ASkateboardCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void ASkateboardCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    MaintainForwardMovement(DeltaTime);
}

void ASkateboardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASkateboardCharacter::Move);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ASkateboardCharacter::StopMove);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASkateboardCharacter::Look);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
    }
}

void ASkateboardCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        if (MovementVector.Y > 0.0f)
        {
            bIsMovingForward = true;
            CurrentSpeed = FMath::Clamp(CurrentSpeed + 10.0f, MinSpeed, MaxSpeed);
        }
        else if (MovementVector.Y < 0.0f)
        {
            CurrentSpeed = FMath::Clamp(CurrentSpeed - 10.0f, MinSpeed, MaxSpeed);
        }
    }
}

void ASkateboardCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
}

void ASkateboardCharacter::StopMove()
{
    bIsMovingForward = false;
}

void ASkateboardCharacter::MaintainForwardMovement(float DeltaTime)
{
    if (Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        AddMovementInput(ForwardDirection, CurrentSpeed / MaxSpeed);
    }
}