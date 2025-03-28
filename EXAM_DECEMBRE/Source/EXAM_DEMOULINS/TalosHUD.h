// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GPE_UI_Widget.h"
#include "TalosHUD.generated.h"

/**
 * 
 */
UCLASS()
class EXAM_DEMOULINS_API ATalosHUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> widgetToCreate = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UUserWidget> currentWidget = nullptr;

public:
	void InitUI();

protected:
	void BeginPlay();

};
