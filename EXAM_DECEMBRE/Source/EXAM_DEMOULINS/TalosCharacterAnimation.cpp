// Fill out your copyright notice in the Description page of Project Settings.


#include "TalosCharacterAnimation.h"
#include "TalosCharacter.h"

void UTalosCharacterAnimation::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ATalosCharacter* _character = Cast<ATalosCharacter>(TryGetPawnOwner());

	if (_character)
		_character->OnForwardMove().AddDynamic(this, &UTalosCharacterAnimation::SetVelocity);
	// TODO BIND SET VELOCITY
}

void UTalosCharacterAnimation::SetVelocity(float _value)
{
	 forwardVelocity = _value; 
}
