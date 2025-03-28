// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE_Locker.h"
#include "GPE_Door.h"


FVector AGPE_Locker::Origin()
{
    return GetActorLocation();
}

void AGPE_Locker::ResetLockerLinks()
{
    isAlimented = false;
    isLinkedByReceptor = false;
}

void AGPE_Locker::BeginPlay()
{
    Super::BeginPlay();
}

void AGPE_Locker::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateLockerDoorStatus();
}

void AGPE_Locker::UpdateLockerDoorStatus()
{
    if (currentDoor)
    {
        if (isAlimented)
            currentDoor->OpenDoor();
        else
            currentDoor->CloseDoor();
    }

}
