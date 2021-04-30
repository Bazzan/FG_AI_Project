// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FGHearingSensingComponent.h"
#include "GameFramework/Actor.h"

#include "NoiseActor.generated.h"

class UNoiseDataAsset;
// class FGAIGameMode;

UCLASS()
class FGAI_API ANoiseActor : public AActor
{
	GENERATED_BODY()



protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ANoiseActor();
	USceneComponent* Root;
	AFGAIGameMode* CurrentGameMode;

	UPROPERTY(EditAnywhere)
	UNoiseDataAsset* NoiseDataSettings;

};
