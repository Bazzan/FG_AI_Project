#include "FGVisionSensingComponent.h"
#include "FGVisionSensingSettings.h"
#include "FGVisionSensingTargetComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

// Line 96 starts the solution for seeing through walls



UFGVisionSensingComponent::UFGVisionSensingComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UFGVisionSensingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (SensingSettings == nullptr)
		return;

	const FVector Direction = GetOwner()->GetActorForwardVector();
	const FVector Origin = GetOwner()->GetActorLocation();

	if (bDebugDrawVision)
	{
		FVector Right = Direction.RotateAngleAxis(SensingSettings->Angle, FVector::UpVector);
		FVector Left = Direction.RotateAngleAxis(-SensingSettings->Angle, FVector::UpVector);
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), Origin, Origin + Right * SensingSettings->DistanceMinimum,
		                                    FLinearColor::Red);
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), Origin, Origin + Left * SensingSettings->DistanceMinimum,
		                                    FLinearColor::Green);
	}

	for (int32 Index = SensedTargets.Num() - 1; Index >= 0; --Index)
	{
		UFGVisionSensingTargetComponent* Target = SensedTargets[Index];

		if (Target == nullptr || (Target != nullptr && Target->IsBeingDestroyed()))
		{
			SensedTargets.RemoveAt(Index);
			continue;
		}

		if (!IsPointVisible(Target->GetTargetOrigin(), Origin, Direction, SensingSettings->DistanceMinimum))
		{
			FFGVisionSensingResults Results;
			Results.SensedActor = Target->GetOwner();
			OnTargetLost.Broadcast(Results);
			SensedTargets.RemoveAt(Index);
		}
	}

	TArray<UFGVisionSensingTargetComponent*> ListOfTargets;

	UFGVisionSensingTargetComponent::GetSensingTargets(ListOfTargets, GetOwner()->GetActorLocation(),
	                                                   SensingSettings->DistanceMinimum);

	for (UFGVisionSensingTargetComponent* Target : ListOfTargets)
	{
		if (!SensedTargets.Contains(Target) &&
			IsPointVisible(Target->GetTargetOrigin(), Origin, Direction, SensingSettings->DistanceMinimum))
		{
			SensedTargets.Add(Target);

			FFGVisionSensingResults Results;
			Results.SensedActor = Target->GetOwner();
			Results.VisionAngle = SensingSettings->Angle;
			Results.VisionDistance = SensingSettings->DistanceMinimum;
			OnTargetSensed.Broadcast(Results);
		}
	}
}

bool UFGVisionSensingComponent::IsPointVisible(const FVector& PointToTest, const FVector& Origin,
                                               const FVector& Direction, float DistanceMinimum
) const
{
	if (SensingSettings == nullptr)
		return false;

	float DistanceMinimumSq = FMath::Square(DistanceMinimum);

	if (FVector::DistSquared(Origin, PointToTest) > DistanceMinimumSq)
	{
		return false;
	}

	const FVector DirectionToTarget = (PointToTest - Origin).GetSafeNormal();

	const float AsHalfRad = FMath::Cos(FMath::DegreesToRadians(SensingSettings->Angle));
	const float Dot = FVector::DotProduct(Direction, DirectionToTarget);

	bool bIsValid = Dot > AsHalfRad;
	
//Solution to seeing throw walls
	if (bIsValid)
	{
		FCollisionQueryParams Params;
		TArray<AActor*> Actors;
		FHitResult Hit;
		UKismetSystemLibrary::LineTraceSingle(GetOwner(), Origin, PointToTest,
		                                      ETraceTypeQuery::TraceTypeQuery2, true, Actors,
		                                      EDrawDebugTrace::ForDuration, Hit, true);

		// check if is actor, if NOT return;
		if(Hit.GetActor() == nullptr) return false;
		if (!Hit.GetActor()->GetComponentByClass(UFGVisionSensingTargetComponent::StaticClass()))
		{
			bIsValid = false;
			UE_LOG(LogTemp, Log, TEXT("lineTrace is not hitting target %s" ), *Hit.GetActor()->GetName());
		}
	}
	return bIsValid;
}

float UFGVisionSensingComponent::GetVisionInRadians() const
{
	if (SensingSettings == nullptr)
		return 0.0;

	return FMath::Cos(FMath::DegreesToRadians(SensingSettings->Angle));
}

