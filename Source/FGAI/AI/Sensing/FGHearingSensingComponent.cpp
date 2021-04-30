#include "FGHearingSensingComponent.h"
#include "FGAI/FGAIGameMode.h"

// Sets default values for this component's properties
UFGHearingSensingComponent::UFGHearingSensingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}



void UFGHearingSensingComponent::BeginPlay()
{
	Super::BeginPlay();

	AFGAIGameMode::HearingActors.Add(GetOwner());
	UE_LOG(LogTemp, Warning, TEXT("SPAWNED ANOTHER, %d"),  (int)AFGAIGameMode::HearingActors.Num());
	


	
}


// // Called every frame
// void UFGHearingSensingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
// 	// ...
// }

