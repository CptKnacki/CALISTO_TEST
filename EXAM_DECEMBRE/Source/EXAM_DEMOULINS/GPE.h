// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE_UI_Component.h"
#include <Components/WidgetComponent.h>
#include "PaperSprite.h"
#include "GPE.generated.h"

UCLASS()
class EXAM_DEMOULINS_API AGPE : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess)) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess)) bool isAlimented = false;
	UPROPERTY(EditAnywhere) TObjectPtr<UWidgetComponent> widgetComponent = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UPaperSprite> interactSprite = nullptr;


public:	
	AGPE();
	FORCEINLINE bool GetIsAlimented() const { return isAlimented; }
	FORCEINLINE void SetIsAlimented(const bool& _value) { isAlimented = _value; }
	virtual FVector Origin();
	virtual FLinearColor GetSourceColor() const;
	UFUNCTION() void ShowUI();
	UFUNCTION() void HideUI();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void InitGPE();
	void UpdateUIWidget();

};
