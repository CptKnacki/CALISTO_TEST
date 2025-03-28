// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE_Receptor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void AGPE_Receptor::ResetReceptorLinks()
{
	alimSource = nullptr;

	if (currentLocker)
		currentLocker->ResetLockerLinks();

	currentLocker = nullptr;
	
	HideNiagara();

}

FVector AGPE_Receptor::Origin()
{
	return GetActorLocation() + GetActorUpVector() * (mesh->GetStaticMesh()->GetBounds().BoxExtent.Z * 1.75);
}

FLinearColor AGPE_Receptor::GetSourceColor() const
{
	if (alimSource && isAlimented)
		return alimSource->GetSourceColor();
	return FLinearColor::White;
}

void AGPE_Receptor::RotateToward()
{
	FRotator _rotation;

	if (!currentLocker)
	{
		if (!alimSource)
			return;

		_rotation = UKismetMathLibrary::FindLookAtRotation(Origin(), alimSource->Origin());
	}
	else _rotation = UKismetMathLibrary::FindLookAtRotation(Origin(), currentLocker->Origin());
	

	_rotation.Pitch = GetActorRotation().Pitch;
	_rotation.Roll = GetActorRotation().Roll;

	SetActorRotation(_rotation);
}

void AGPE_Receptor::BeginPlay()
{
	Super::BeginPlay();
	InitNiagara();
}

void AGPE_Receptor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebug();
	ConnexionTest();
}

void AGPE_Receptor::InitNiagara()
{
	if (talosBeamFX && !alimSourceBeam && !lockerBeam)
	{
		alimSourceBeam = UNiagaraFunctionLibrary::SpawnSystemAttached(talosBeamFX, mesh, FName("alimSourceBeam"),
			FVector(0, 0, -100), FRotator(), EAttachLocation::KeepRelativeOffset, true);

		lockerBeam = UNiagaraFunctionLibrary::SpawnSystemAttached(talosBeamFX, mesh, FName("lockerBeam"),
			FVector(0, 0, -100), FRotator(), EAttachLocation::KeepRelativeOffset, true);
	}

	HideNiagara();
}

void AGPE_Receptor::HideNiagara()
{
	if (alimSourceBeam)
		alimSourceBeam->SetVisibility(false);

	if (lockerBeam)
		lockerBeam->SetVisibility(false);
}

void AGPE_Receptor::ShowNiagara()
{
	if (alimSourceBeam)
		alimSourceBeam->SetVisibility(true);

	if (lockerBeam)
		lockerBeam->SetVisibility(true);
}

void AGPE_Receptor::DrawDebug()
{

	if (alimSource && alimSourceBeam)
	{
		alimSourceBeam->SetNiagaraVariableVec3(FString("StartPoint"), Origin());
		alimSourceBeam->SetNiagaraVariableVec3(FString("EndPoint"), alimSource->Origin());

		FLinearColor _color = (isAlimented) ? GetSourceColor() : FLinearColor::White;
		alimSourceBeam->SetColorParameter(FName("Color"), _color);

		alimSourceBeam->SetVisibility(true);
	}
	

	if (currentLocker && lockerBeam)
	{
		lockerBeam->SetNiagaraVariableVec3(FString("StartPoint"), Origin());
		lockerBeam->SetNiagaraVariableVec3(FString("EndPoint"), currentLocker->Origin());

		FLinearColor _color = (currentLocker->GetIsAlimented()) ? GetSourceColor() : FLinearColor::White;
		lockerBeam->SetColorParameter(FName("Color"), _color);

		lockerBeam->SetVisibility(true);
	}
}

void AGPE_Receptor::ConnexionTest()
{
	FVector _origin = Origin();
	FHitResult _result;
	TArray<AActor*> _actorsToIgnore;
	
	
	if (alimSource && alimSource->GetIsAlimented())
	{
		_actorsToIgnore.Add(alimSource);
		FVector _direction = -(Origin() - alimSource->Origin());

		bool _hit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), _origin, _origin + _direction, connexionCollisionLayers,
			true, _actorsToIgnore, EDrawDebugTrace::None, _result, true);

		isAlimented = !_hit;

	}
	else isAlimented = false;
	
	if (currentLocker)
	{
		if (!isAlimented)
		{
			currentLocker->SetIsAlimented(isAlimented);
			return;
		}

		_actorsToIgnore.Add(currentLocker);
		FVector _direction = -(Origin() - currentLocker->Origin());

		bool _hit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), _origin, _origin + _direction, connexionCollisionLayers,
			true, _actorsToIgnore, EDrawDebugTrace::None, _result, true);

		currentLocker->SetIsAlimented(!_hit);

	}
}

