// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPE.h"
#include "GPE_Source.generated.h"

/**
 * 
 */
UCLASS()
class EXAM_DEMOULINS_API AGPE_Source : public AGPE
{
	GENERATED_BODY()
	

public:
	virtual FVector Origin() override;
	virtual FLinearColor GetSourceColor() const override;
};
