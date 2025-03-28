

#include "TalosCharacter.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

ATalosCharacter::ATalosCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>("springArm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	springArm->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);

	interactComponent = CreateDefaultSubobject<UTalosInteractComponent>("Interact Component");
	AddOwnedComponent(interactComponent);

	interactWidget = CreateDefaultSubobject<UWidgetComponent>("Interact Widget");
	AddOwnedComponent(interactWidget);
}


void ATalosCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitInteractWidget();
}

void ATalosCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateCameraLookAt();
	DetectInteractableObjects();
	UpdateInteractWidget();
}


void ATalosCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InitInputs();

	UEnhancedInputComponent* _input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	_input->BindAction(forwardMove, ETriggerEvent::Triggered, this, &ATalosCharacter::MoveForward);
	_input->BindAction(forwardMove, ETriggerEvent::Completed, this, &ATalosCharacter::EndMoveForward);
	_input->BindAction(rotate, ETriggerEvent::Triggered, this, &ATalosCharacter::Rotate);
	_input->BindAction(interact, ETriggerEvent::Started, this, &ATalosCharacter::Interact);
	_input->BindAction(drop, ETriggerEvent::Started, this, &ATalosCharacter::Drop);
	_input->BindAction(reset, ETriggerEvent::Started, this, &ATalosCharacter::ResetLinks);

}

void ATalosCharacter::InitInteractWidget()
{
	interactWidget->SetVisibility(false);
}

void ATalosCharacter::UpdateInteractWidget()
{
	FRotator _rotation = UKismetMathLibrary::FindLookAtRotation(interactWidget->GetComponentLocation(), GetCameraLocation());
	interactWidget->SetWorldRotation(_rotation);
}

void ATalosCharacter::InitInputs()
{
	APlayerController* _p = GetWorld()->GetFirstPlayerController();

	UEnhancedInputLocalPlayerSubsystem* _inputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(_p->GetLocalPlayer());
	_inputSystem->ClearAllMappings();
	_inputSystem->AddMappingContext(inputMapping.LoadSynchronous(), 0);

}

void ATalosCharacter::MoveForward(const FInputActionValue& _value)
{
	float _forwardAxis = _value.Get<float>();

	AddMovementInput(GetActorForwardVector() * _forwardAxis);

	onForwardMove.Broadcast(_forwardAxis);
}

void ATalosCharacter::EndMoveForward(const FInputActionValue& _value)
{
	onForwardMove.Broadcast(0);
}

void ATalosCharacter::Rotate(const FInputActionValue& _value)
{
	FVector2D _rotateVector = _value.Get<FVector2D>();

	AddControllerYawInput(_rotateVector.X);

	FRotator _rotation = springArm->GetRelativeRotation();
	_rotation.Pitch = FMath::Clamp(_rotation.Pitch + _rotateVector.Y , maxSpringArmPitch, 0);
	springArm->SetRelativeRotation(_rotation);

}

void ATalosCharacter::Interact(const FInputActionValue& _value)
{
	bool _interact = _value.Get<bool>();

	if (_interact && canInteract)
	{
		if (!interactComponent)
		{
			UKismetSystemLibrary::PrintString(this, "component is null !");
		}
		else interactComponent->TripodInteraction(currentlyAimedReceptor);
	}

}

void ATalosCharacter::Drop(const FInputActionValue& _value)
{
	bool _dropValue = _value.Get<bool>();

	if (_dropValue && interactComponent)
		interactComponent->Drop();
}

void ATalosCharacter::ResetLinks(const FInputActionValue& _value)
{

	bool _resetValue = _value.Get<bool>();

	if (_resetValue && interactComponent)
		interactComponent->ResetCurrentTripodLink();
}

void ATalosCharacter::UpdateCameraLookAt()
{
	float _pitchDelta = springArm->GetRelativeRotation().Pitch / maxSpringArmPitch;
	FVector _aimLocation = GetActorLocation() + GetActorForwardVector() * interactRange + FVector(0, 0, interactRange * 0.5f) - FVector(0, 0, interactRange) * _pitchDelta;
	
	FRotator _result = UKismetMathLibrary::FindLookAtRotation(camera->GetComponentLocation(), _aimLocation);

	camera->SetWorldRotation(_result);
}

void ATalosCharacter::DetectInteractableObjects()
{
	FVector _origin = camera->GetComponentLocation(),
		_direction = camera->GetForwardVector();

	FVector _interactLocation = FVector(-1);

	if (interactComponent && interactComponent->IsGrabbing())
	{
		_interactLocation = interactComponent->DetectInteractablesObject(_origin, _direction);
	}
	else
	{
		FHitResult _result;

		bool _hit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), _origin, _origin + _direction * interactRange, receptorLayer,
			true, TArray<AActor*>(), EDrawDebugTrace::None, _result, true);

		if (_hit)
		{
			currentlyAimedReceptor = Cast<AGPE_Receptor>(_result.GetActor());
			canInteract = (currentlyAimedReceptor != nullptr);
			_interactLocation = currentlyAimedReceptor->GetActorLocation() + FVector(0, 0, 100);
		}
		else
		{
			currentlyAimedReceptor = nullptr;
			canInteract = false;
		}
	}
	

	if (_interactLocation != FVector(-1))
	{
		interactWidget->SetWorldLocation(_interactLocation);
		interactWidget->SetVisibility(true);
	}
	else interactWidget->SetVisibility(false);

}

