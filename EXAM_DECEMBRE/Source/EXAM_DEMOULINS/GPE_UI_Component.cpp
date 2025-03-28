// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE_UI_Component.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Kismet/KismetMathLibrary.h>
#include "TalosCharacter.h"

UGPE_UI_Component::UGPE_UI_Component()
{
	PrimaryComponentTick.bCanEverTick = true;

}



void UGPE_UI_Component::BeginPlay()
{
	Super::BeginPlay();
	InitUI();
}


void UGPE_UI_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateUI();
}

void UGPE_UI_Component::InitUI()
{
	widgetComponent->SetWorldLocation(GetOwner()->GetActorLocation());

	UGPE_UI_Widget* _widget = Cast<UGPE_UI_Widget>(widgetComponent->GetWidget());

	if (_widget)
		_widget->GetInteractIcon()->SetBrushResourceObject(interactSprite);

	ATalosCharacter* _character = Cast<ATalosCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (_character)
	{
		_character->InteractComponent()->OnReceptorTaken().AddDynamic(this, &UGPE_UI_Component::ShowUI);
		_character->InteractComponent()->OnReceptorDrop().AddDynamic(this, &UGPE_UI_Component::HideUI);
	}


	HideUI();
}

void UGPE_UI_Component::UpdateUI()
{
	ATalosCharacter* _character = Cast<ATalosCharacter>(GetOwner());

	if (_character)
	{
		FRotator _rotation = UKismetMathLibrary::FindLookAtRotation(widgetComponent->GetComponentLocation(), _character->GetCameraLocation());
		widgetComponent->SetWorldRotation(_rotation);
	}

	widgetComponent->SetWorldLocation(GetOwner()->GetActorLocation());
}

void UGPE_UI_Component::ShowUI()
{
	if (widgetComponent)
		widgetComponent->SetVisibility(true);
}

void UGPE_UI_Component::HideUI()
{
	if (widgetComponent)
		widgetComponent->SetVisibility(false);
}