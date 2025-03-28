// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include "GPE_UI_Widget.generated.h"

/**
 * 
 */
UCLASS()
class EXAM_DEMOULINS_API UGPE_UI_Widget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UImage> interactIcon = nullptr;

public:
	FORCEINLINE TObjectPtr<UImage>& GetInteractIcon() { return interactIcon; }

};
