// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FGAIGameMode.generated.h"

UCLASS(minimalapi)
class AFGAIGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	AFGAIGameMode();

	// UPROPERTY(VisibleAnywhere)
	static TArray<AActor*> HearingActors; 
};



