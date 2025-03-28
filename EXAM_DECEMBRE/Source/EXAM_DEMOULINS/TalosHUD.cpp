// Fill out your copyright notice in the Description page of Project Settings.


#include "TalosHUD.h"
#include "Kismet/KismetSystemLibrary.h"

void ATalosHUD::BeginPlay()
{
	Super::BeginPlay();
	InitUI();
}

void ATalosHUD::InitUI()
{
	if (!widgetToCreate)
		return;

	currentWidget = CreateWidget(GetWorld(), widgetToCreate);
	currentWidget->AddToViewport();

}