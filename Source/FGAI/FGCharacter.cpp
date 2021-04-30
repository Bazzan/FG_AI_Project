#include "FGCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/FGMovementComponent.h"
#include "FGMovementStatics.h"
#include "AI/ThrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AI/ThrowComponent.h"

class UThrowComponent;

AFGCharacter::AFGCharacter()
{
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	// Set size for collision capsule
	Capsule->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 2.5f;
	BaseLookUpRate = 2.5f;

	Speed = 1000.0f;
	Gravity = 900.0f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(Capsule);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	Mesh->SetOnlyOwnerSee(true);
	Mesh->SetupAttachment(FirstPersonCameraComponent);
	Mesh->bCastDynamicShadow = false;
	Mesh->CastShadow = false;
	Mesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	MovementComponent = CreateDefaultSubobject<UFGMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(Capsule);
}

void AFGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FFGFrameMovement FrameMovement = MovementComponent->CreateFrameMovement();

	if (JumpVector.Z > 0.01f)
	{
		FrameMovement.AddGravity(-JumpVector.Z * DeltaTime);
		JumpVector.Z *= 0.9f - DeltaTime;
	}

	FrameMovement.AddGravity(Gravity * DeltaTime);


	if (!InputVector.IsNearlyZero())
	{
		FVector Forward =
			FVector::VectorPlaneProject(FirstPersonCameraComponent->GetForwardVector(), FVector::UpVector);
		FVector ForwardMovement = Forward * InputVector.X;
		FVector Right = FirstPersonCameraComponent->GetRightVector() * InputVector.Y;
		FVector Velocity = (ForwardMovement + Right).GetSafeNormal() * Speed * DeltaTime;
		if (bJump)
		{
			Velocity.Z += JumpHeight * DeltaTime;
			bJump = false;
		}


		FrameMovement.AddDelta(Velocity);
	}


	MovementComponent->Move(FrameMovement);
}

void AFGCharacter::BeginPlay()
{
	Super::BeginPlay();
	throwComponent = Cast<UThrowComponent>(
		GetComponentByClass(TSubclassOf<UThrowComponent>(UThrowComponent::StaticClass())));
}

void AFGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFGCharacter::OnFire);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFGCharacter::OnJump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFGCharacter::OnChrouch);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFGCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently

	PlayerInputComponent->BindAxis("Turn", this, &AFGCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AFGCharacter::LookUpAtRate);
}

void AFGCharacter::OnJump()
{
	JumpVector.Z = JumpHeight;
}

void AFGCharacter::OnChrouch()
{
	if (!bIsCrouching)
	{
		Capsule->SetCapsuleSize(Capsule->GetScaledCapsuleRadius() / 3, Capsule->GetScaledCapsuleHalfHeight() / 3);
		bIsCrouching = true;
		UE_LOG(LogTemp, Display, TEXT("Chrouch"))
	}
	else
	{
		Capsule->SetCapsuleSize(Capsule->GetScaledCapsuleRadius() * 3, Capsule->GetScaledCapsuleHalfHeight() * 3);
		bIsCrouching = false;
		UE_LOG(LogTemp, Display, TEXT("UN Chrouch"))
	}
}


void AFGCharacter::OnFire()
{
	throwComponent->ThrowObject();
}


void AFGCharacter::MoveForward(float Value)
{
	InputVector.X = Value;
}

void AFGCharacter::MoveRight(float Value)
{
	InputVector.Y = Value;
}

void AFGCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate);
}

void AFGCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate);
}
