// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowingObject.h"
#include "Components/StaticMeshComponent.h"
#include "FGAI/FGAIGameMode.h"
#include "Sensing/NoiseComponent.h"
// Sets default values
AThrowingObject::AThrowingObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AThrowingObject::BeginPlay()
{
	Super::BeginPlay();

	Hit.Init();
	Velocity = GetActorForwardVector() * ThrowForce;
	mesh = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
}

// Called every frame
void AThrowingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(NoiseData == nullptr) return;
	if (!Hit.bBlockingHit)
	{
		Velocity -= FVector(0.0, 0.0f, 980.f) * DeltaTime;
		AddActorWorldOffset(Velocity * DeltaTime, true, &Hit);
	}


	if (Hit.bBlockingHit)
	{
		if(AFGAIGameMode::HearingActors.Num() < 1)return;
		UNoiseComponent* noiseComp = Cast<UNoiseComponent>(
			GetOwner()->GetComponentByClass(UNoiseComponent::StaticClass()));
		noiseComp->SpawnNoise(GetActorTransform(), this, NoiseData);
		mesh->SetSimulatePhysics(true);

		PrimaryActorTick.bCanEverTick = false;
		PrimaryActorTick.SetTickFunctionEnable(false);
		UE_LOG(LogTemp, Display, TEXT("Rock made Nosie"));
	}

}
