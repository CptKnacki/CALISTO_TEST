// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GPE_Receptor.h"
#include "TalosInteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXAM_DEMOULINS_API UTalosInteractComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReceptorTaken);
		FOnReceptorTaken onReceptorTaken;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReceptorDrop);
		FOnReceptorDrop onReceptorDrop;

	UPROPERTY(EditAnywhere) TArray<TEnumAsByte<EObjectTypeQuery>> interactableLayers;
	UPROPERTY(EditAnywhere) TArray<TEnumAsByte<EObjectTypeQuery>> snapLayers;
	UPROPERTY(EditAnywhere) TObjectPtr<AGPE_Receptor> currentReceptor = nullptr;
	UPROPERTY(EditAnywhere) bool isGrabbing = false;
	UPROPERTY() TArray<AActor*> ignoredActors;
	UPROPERTY() TObjectPtr<AGPE> currentlyAimedGPE = nullptr;

public:	
	UTalosInteractComponent();

	FORCEINLINE FOnReceptorTaken& OnReceptorTaken() { return onReceptorTaken; }
	FORCEINLINE FOnReceptorDrop& OnReceptorDrop() { return onReceptorDrop; }
	FORCEINLINE bool IsGrabbing() { return isGrabbing; }

	FVector DetectInteractablesObject(FVector _origin, FVector _direction);
	void TripodInteraction(TObjectPtr<AGPE_Receptor> _actor);
	void ResetCurrentTripodLink();
	void Drop();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Grab(TObjectPtr<AGPE_Receptor> _actor);
	void DetermineCurrentInteraction();
};
