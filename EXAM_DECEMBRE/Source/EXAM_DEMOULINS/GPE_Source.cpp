// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE_Source.h"
#include "Materials/Material.h"
#include <Kismet/KismetSystemLibrary.h>

FVector AGPE_Source::Origin()
{
	return GetActorLocation();
}

FLinearColor AGPE_Source::GetSourceColor() const
{
	UMaterialInterface* _material = mesh->GetMaterial(0);

	FMemoryImageMaterialParameterInfo _info;
	_info.Name = FScriptName("BaseColor");

	FMaterialParameterMetadata _value;

	if (_material->GetParameterValue(EMaterialParameterType::Vector, _info, _value))
		return _value.Value.AsLinearColor();

	return FLinearColor::Green;

}

