// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPE.h"
#include "GPE_Locker.generated.h"

/**
 * 
 */
UCLASS()
class EXAM_DEMOULINS_API AGPE_Locker : public AGPE
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) TObjectPtr<class AGPE_Door> currentDoor = nullptr;
	bool isLinkedByReceptor = false;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess)) FLinearColor sourceColor = FLinearColor::White;

public:
	FORCEINLINE void SetIsLinked(const bool& _value) { isLinkedByReceptor = _value; }
	FORCEINLINE void SetSourceColor(const FLinearColor& _value) { sourceColor = _value; }
	FORCEINLINE bool GetIsLinked() const { return isLinkedByReceptor; }
	virtual FVector Origin() override;
	void ResetLockerLinks();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void UpdateLockerDoorStatus();
};
