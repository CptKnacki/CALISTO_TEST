// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE_Door.h"

AGPE_Door::AGPE_Door()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	RootComponent = mesh;
}

void AGPE_Door::OpenDoor()
{
	mesh->SetVisibility(false);
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AGPE_Door::CloseDoor()
{
	mesh->SetVisibility(true);
	mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
