// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseActor.h"
#include "NoiseDataAsset.h"
#include "DrawDebugHelpers.h"
#include "FGAI/FGAIGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "FGHearingSensingComponent.h"

// Sets default values
ANoiseActor::ANoiseActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
}


// Called when the game starts or when spawned
void ANoiseActor::BeginPlay()
{
	Super::BeginPlay();


	UE_LOG(LogTemp, Warning, TEXT("Spawned a NoiseActor and there are this meny HearingActors: %d"),
	       AFGAIGameMode::HearingActors.Num());
}

TArray<AActor*> AFGAIGameMode::HearingActors;

// Called every frame
void ANoiseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (NoiseDataSettings == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NoiseDataSettings == nullptr"));
		return;
	}

	DrawDebugSphere(GetWorld(), GetActorLocation(), NoiseDataSettings->Radius, 16, FColor::Red);

	for (auto HearingActor : AFGAIGameMode::HearingActors)
	{
		if (HearingActor == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("HearingActor == nullptr"));

			return;
		}
		float distanceSqred = FVector::DistSquared(GetActorLocation(), HearingActor->GetActorLocation());
		if (distanceSqred < NoiseDataSettings->Radius * NoiseDataSettings->Radius)
		{
			UFGHearingSensingComponent* hearingComp = Cast<UFGHearingSensingComponent>(
				HearingActor->GetComponentByClass(UFGHearingSensingComponent::StaticClass()));

			// if(hearingComp == nullptr) return ;
			FNoiseData NoiseDataResult;
			NoiseDataResult.Raidus = NoiseDataSettings->Radius;
			NoiseDataResult.NoiseActor = this;
			NoiseDataResult.Instagator = GetOwner();

			hearingComp->OnHearingEvent.Broadcast(NoiseDataResult);
			UE_LOG(LogTemp, Warning, TEXT("hearingEvent broadcasted"));
		}
	}

	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.SetTickFunctionEnable(false);
}
