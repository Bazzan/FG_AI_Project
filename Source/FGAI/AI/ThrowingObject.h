// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowingObject.generated.h"

class UNoiseDataAsset;
class UStaticMeshComponent;

UCLASS()
class FGAI_API AThrowingObject : public AActor
{
	GENERATED_BODY()
private:
	FHitResult Hit;
	UStaticMeshComponent* mesh;

	FVector Velocity;
	AActor* instagator;
public:
	UPROPERTY(EditAnywhere)
	UNoiseDataAsset* NoiseData;

	UPROPERTY(EditAnywhere)
	float ThrowForce;
	FVector ForwardVector = FVector::ZeroVector;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:


	// Sets default values for this actor's properties
	AThrowingObject();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
