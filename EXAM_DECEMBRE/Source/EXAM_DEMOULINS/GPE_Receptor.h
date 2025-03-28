// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPE.h"
#include "GPE_Locker.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GPE_Receptor.generated.h"

/**
 * 
 */
UCLASS()
class EXAM_DEMOULINS_API AGPE_Receptor : public AGPE
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<AGPE> alimSource = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<AGPE_Locker> currentLocker = nullptr;
	UPROPERTY(EditAnywhere) TArray<TEnumAsByte<EObjectTypeQuery>> connexionCollisionLayers;

	UPROPERTY(EditAnywhere, Category = "Niagara") TObjectPtr<UNiagaraSystem> talosBeamFX = nullptr;
	UPROPERTY() TObjectPtr<UNiagaraComponent> alimSourceBeam = nullptr;
	UPROPERTY() TObjectPtr<UNiagaraComponent> lockerBeam = nullptr;

public:
	FORCEINLINE void SetAlimSource(const TObjectPtr<AGPE>& _source) { alimSource = _source; }
	FORCEINLINE void SetCurrentLocker(const TObjectPtr<AGPE_Locker>& _locker) { currentLocker = _locker; }
	virtual FVector Origin() override;
	virtual FLinearColor GetSourceColor() const override;
	void RotateToward();
	void ResetReceptorLinks();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void DrawDebug();
	void ConnexionTest();
	void InitNiagara();
	void HideNiagara();
	void ShowNiagara();
	
};
