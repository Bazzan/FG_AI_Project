// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowComponent.h"
#include <concrt.h>

// Sets default values for this component's properties
UThrowComponent::UThrowComponent()
{

}




void UThrowComponent::ThrowObject()
{
	FActorSpawnParameters Parameters;
	Parameters.Owner = GetOwner();
	
	
	AThrowingObject* rock = GetWorld()->SpawnActor<AThrowingObject>(ThrowingObject,
	                                                                GetOwner()->GetActorLocation() + GetOwner()->
	                                                                GetActorForwardVector() * 100.f,
	                                                                GetOwner()->GetActorRotation(),Parameters);
	rock->ThrowForce = ThrowForce;
	rock->ForwardVector = GetOwner()->GetActorForwardVector();
	rock->SetOwner(GetOwner());
}
