// Fill out your copyright notice in the Description page of Project Settings.


#include "Inputs_UI_Display.h"

// Sets default values
AInputs_UI_Display::AInputs_UI_Display()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	RootComponent = mesh;

	widgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	AddOwnedComponent(widgetComponent);
}

// Called when the game starts or when spawned
void AInputs_UI_Display::BeginPlay()
{
	Super::BeginPlay();


	widgetComponent->SetWorldLocation(GetActorLocation());
}

// Called every frame
void AInputs_UI_Display::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

