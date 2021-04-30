// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseComponent.h"
#include "NoiseActor.h"
#include "NoiseDataAsset.h"
#include "Components/SceneComponent.h"


// Sets default values for this component's properties
UNoiseComponent::UNoiseComponent()
{

}


void UNoiseComponent::SpawnNoise(FTransform Transform , AActor* ActorThatMakeNoise, UNoiseDataAsset* NoiseData)
{
	SpawnParameters.Owner = GetOwner();
	
	auto noiseActor = GetWorld()->SpawnActor<ANoiseActor>(ANoiseActor::StaticClass() ,Transform.GetLocation(),Transform.Rotator(),SpawnParameters);
	noiseActor->NoiseDataSettings = NoiseData;
}




