// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NoiseComponent.generated.h"


class USceneComponent;
class UNoiseDataAsset;
class ANoiseActor;

UCLASS(Blueprintable)
class FGAI_API UNoiseComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	FActorSpawnParameters SpawnParameters;
	ANoiseActor* NoiseActor;
public:
	// Called every frame
	UNoiseComponent();

	UFUNCTION(BlueprintCallable)
	void SpawnNoise(FTransform Transform, AActor* ActorThatMakeNoise, UNoiseDataAsset* NoiseData);

	
};

