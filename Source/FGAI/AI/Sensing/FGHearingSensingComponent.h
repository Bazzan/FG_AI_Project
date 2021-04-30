
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NoiseDataAsset.h"
#include "Components/ActorComponent.h"
#include "FGHearingSensingComponent.generated.h"


class AFGAIGameMode;

USTRUCT(BlueprintType)
struct FNoiseData
{

	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	AActor* NoiseActor;
	UPROPERTY(BlueprintReadOnly)
	AActor* Instagator;
	UPROPERTY(BlueprintReadOnly)
	float Raidus;
	
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFGHearingSensingDelegate, const FNoiseData&, NoiseDataResult);

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UFGHearingSensingComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	AFGAIGameMode* CurrentGameMode;

	UPROPERTY(BlueprintAssignable)
	FFGHearingSensingDelegate OnHearingEvent;	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFGHearingSensingComponent();
	
	
	// Called every frame
	// virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
