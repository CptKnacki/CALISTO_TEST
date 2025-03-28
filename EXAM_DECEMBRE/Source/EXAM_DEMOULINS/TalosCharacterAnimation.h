// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TalosCharacterAnimation.generated.h"

/**
 * 
 */
UCLASS()
class EXAM_DEMOULINS_API UTalosCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess)) float forwardVelocity = 0.0f;

public:

protected:
	virtual void NativeBeginPlay() override;
	UFUNCTION() void SetVelocity(float _value); 
};
