#include "FGAIGameMode.h"

void AFGAIGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	AFGAIGameMode::HearingActors.Empty();
	int i = 0;
}

AFGAIGameMode::AFGAIGameMode()
	: Super()
{

}
