#pragma once

#include "Engine/DataAsset.h"
#include "NoiseDataAsset.generated.h"

class ANoiseActor;
UCLASS()
class UNoiseDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere)
	float Radius;
};
