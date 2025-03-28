// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPE.h"
#include "GPE_Door.generated.h"

/**
 * 
 */
UCLASS()
class EXAM_DEMOULINS_API AGPE_Door : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)	TObjectPtr<UStaticMeshComponent> mesh = nullptr;

public:
	AGPE_Door();
	void OpenDoor();
	void CloseDoor();
};
