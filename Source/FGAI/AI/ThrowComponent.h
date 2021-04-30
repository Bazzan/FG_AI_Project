// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ThrowingObject.h"
#include "Components/ActorComponent.h"
#include "ThrowComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FGAI_API UThrowComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	float ThrowForce;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AThrowingObject> ThrowingObject;
	

public:
	UThrowComponent();
	// Called every frame
	void ThrowObject();		
};
