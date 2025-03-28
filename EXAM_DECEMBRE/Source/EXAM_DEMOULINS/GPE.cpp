// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE.h"
#include "TalosCharacter.h"
#include <Kismet/KismetMathLibrary.h>

AGPE::AGPE()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = mesh;

	widgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	AddOwnedComponent(widgetComponent);
}

FVector AGPE::Origin()
{
	return FVector();
}

FLinearColor AGPE::GetSourceColor() const
{
	return FLinearColor::Red;
}

void AGPE::ShowUI()
{
	widgetComponent->SetVisibility(true);
}

void AGPE::HideUI()
{
	widgetComponent->SetVisibility(false);
}

void AGPE::BeginPlay()
{
	Super::BeginPlay();
	InitGPE();
}

void AGPE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateUIWidget();
}

void AGPE::InitGPE()
{
	widgetComponent->SetWorldLocation(GetActorLocation());

	UGPE_UI_Widget* _widget = Cast<UGPE_UI_Widget>(widgetComponent->GetWidget());

	if (_widget)
		_widget->GetInteractIcon()->SetBrushResourceObject(interactSprite);

	ATalosCharacter* _character = Cast<ATalosCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (_character)
	{
		_character->InteractComponent()->OnReceptorTaken().AddDynamic(this, &AGPE::ShowUI);
		_character->InteractComponent()->OnReceptorDrop().AddDynamic(this, &AGPE::HideUI);
	}

	
	HideUI();

}

void AGPE::UpdateUIWidget()
{
	ATalosCharacter* _character = Cast<ATalosCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (_character)
	{
		FRotator _rotation = UKismetMathLibrary::FindLookAtRotation(widgetComponent->GetComponentLocation(), _character->GetCameraLocation());
		widgetComponent->SetWorldRotation(_rotation);
	}
	widgetComponent->SetWorldLocation(GetActorLocation());
}

