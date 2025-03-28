// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GPE_UI_Widget.h"
#include "PaperSprite.h"
#include <Components/WidgetComponent.h>
#include "GPE_UI_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXAM_DEMOULINS_API UGPE_UI_Component : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UPaperSprite> interactSprite = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UWidgetComponent> widgetComponent = nullptr;

public:	
	UGPE_UI_Component();
	UFUNCTION() void ShowUI();
	UFUNCTION() void HideUI();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void InitUI();
	void UpdateUI();
};
