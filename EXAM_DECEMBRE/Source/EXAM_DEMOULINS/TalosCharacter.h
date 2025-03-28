// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "TalosInteractComponent.h"
#include "TalosCharacter.generated.h"

UCLASS()
class EXAM_DEMOULINS_API ATalosCharacter : public ACharacter
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnForwardMove, float, velocity);
	FOnForwardMove onForwardMove;

#pragma region EnhancedInputs

	UPROPERTY(EditAnywhere) TSoftObjectPtr<UInputMappingContext> inputMapping = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> forwardMove = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> rotate = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> interact = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> reset = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> drop = nullptr;

#pragma endregion

#pragma region Camera

	UPROPERTY(EditAnywhere) TObjectPtr<USpringArmComponent> springArm = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UCameraComponent> camera = nullptr;
	UPROPERTY(EditAnywhere) int maxSpringArmPitch = -45;
#pragma endregion

#pragma region Interact/Linetrace

	UPROPERTY(EditAnywhere) TObjectPtr<UTalosInteractComponent> interactComponent = nullptr;
	UPROPERTY(EditAnywhere) TArray<TEnumAsByte<EObjectTypeQuery>> receptorLayer;
	UPROPERTY() TObjectPtr<AGPE_Receptor> currentlyAimedReceptor = nullptr;
	UPROPERTY(EditAnywhere)float interactRange = 650.0f;
	bool canInteract = false;

	

#pragma endregion

#pragma region UI
	UPROPERTY(EditAnywhere) TObjectPtr<UWidgetComponent> interactWidget = nullptr;

#pragma endregion

public:
	ATalosCharacter();
	FORCEINLINE FOnForwardMove& OnForwardMove() { return onForwardMove; }
	FORCEINLINE TObjectPtr<UTalosInteractComponent> InteractComponent() { return interactComponent; }
	FORCEINLINE FVector GetCameraLocation() const { return camera->GetComponentLocation(); }
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void InitInteractWidget();
	void UpdateInteractWidget();

	void InitInputs();
	void MoveForward(const FInputActionValue& _value);
	void EndMoveForward(const FInputActionValue& _value);
	void Rotate(const FInputActionValue& _value);
	void Interact(const FInputActionValue& _value);
	void Drop(const FInputActionValue& _value);
	void ResetLinks(const FInputActionValue& _value);

	void UpdateCameraLookAt();
	void DetectInteractableObjects();
};
