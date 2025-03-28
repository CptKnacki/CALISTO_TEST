// Fill out your copyright notice in the Description page of Project Settings.


#include "TalosInteractComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GPE_Source.h"

UTalosInteractComponent::UTalosInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UTalosInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UTalosInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UTalosInteractComponent::Grab(TObjectPtr<AGPE_Receptor> _receptor)
{

	currentReceptor = _receptor;
	FVector _location = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 100;
	currentReceptor->SetActorLocation(_location);
	currentReceptor->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
	ignoredActors.Add(currentReceptor);
	isGrabbing = true;

	onReceptorTaken.Broadcast();
}

FVector UTalosInteractComponent::DetectInteractablesObject(FVector _origin, FVector _direction)
{
	if (!currentReceptor || !isGrabbing)
		return FVector(-1);

	FHitResult _result;

	bool _hit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), _origin, _origin + _direction * 5000, interactableLayers,
		true, ignoredActors, EDrawDebugTrace::None, _result, true);

	if (_hit)
	{
		currentlyAimedGPE = Cast<AGPE>(_result.GetActor());
		return currentlyAimedGPE->GetActorLocation() + FVector(0, 0, 100);
	}
	else
		currentlyAimedGPE = nullptr;

	return FVector(-1);
}

void UTalosInteractComponent::DetermineCurrentInteraction()
{
	if (!currentlyAimedGPE)
		return;

	AGPE_Source* _source = Cast<AGPE_Source>(currentlyAimedGPE);

	if (_source)
	{
		currentReceptor->SetAlimSource(_source);
		return;
	}

	AGPE_Receptor* _receptor = Cast<AGPE_Receptor>(currentlyAimedGPE);

	if (_receptor && _receptor->GetIsAlimented())
	{
		currentReceptor->SetAlimSource(_receptor);
		return;
	}

	AGPE_Locker* _locker = Cast<AGPE_Locker>(currentlyAimedGPE);

	if (_locker && !_locker->GetIsLinked())
	{
		currentReceptor->SetCurrentLocker(_locker);
		_locker->SetIsLinked(true);
		_locker->SetSourceColor(currentReceptor->GetSourceColor());
		return;
	}

}

void UTalosInteractComponent::Drop()
{
	if (!currentReceptor)
		return;

	FHitResult _result;

	FVector _origin = currentReceptor->GetActorLocation(),
		_direction = - currentReceptor->GetActorUpVector();

	bool _hit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), _origin, _origin + _direction * 500, snapLayers,
		true, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, _result, true);

	if (_hit)
	{
		currentReceptor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		currentReceptor->SetActorLocation(_result.ImpactPoint);
		currentReceptor->RotateToward();
		currentReceptor = nullptr;
		ignoredActors.Empty();
		isGrabbing = false;
		onReceptorDrop.Broadcast();
	}

}

void UTalosInteractComponent::ResetCurrentTripodLink()
{
	if (currentReceptor)
		currentReceptor->ResetReceptorLinks();
}

void UTalosInteractComponent::TripodInteraction(TObjectPtr<AGPE_Receptor> _receptor)
{

	if(!isGrabbing && !currentReceptor && _receptor != nullptr)
	{
		Grab(_receptor);
		return;
	}

	if (currentlyAimedGPE)
		DetermineCurrentInteraction();
}

