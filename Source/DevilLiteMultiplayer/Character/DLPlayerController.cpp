// Fill out your copyright notice in the Description page of Project Settings.


#include "DLPlayerController.h"
#include "GameFramework/Pawn.h"
#include "DLPlayerCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "DevilLiteMultiplayer/DataAssets/MouseGlobalEvents.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ADLPlayerController::ADLPlayerController()
{
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;
	DefaultClickTraceChannel = mouseRegesterableChannel;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ADLPlayerController::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		CachedPlayerCharacter = Cast<ADLPlayerCharacter>(ControlledPawn);
		if (CachedPlayerCharacter == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("This controller is only supposed to work with a player character, but assigned pawn is not a DLPlayerCharacter"));
		}
	}

	if(MouseGlobalEvents != nullptr)
	{
		MouseGlobalEvents->OnMouseHitRegisteredEvent.AddDynamic(this, &ADLPlayerController::OnMouseHitObjectChanged);
		OnDestroyed.AddDynamic(this, &ADLPlayerController::OnDestroyedEventCallback);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The Mouse Global Event data asset is not assigned in the player controller"));
	}
}

void ADLPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ADLPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ADLPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ADLPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ADLPlayerController::OnSetDestinationReleased);
		
		EnhancedInputComponent->BindAction(MouseScrollAction, ETriggerEvent::Triggered, this, &ADLPlayerController::OnMouseScrollTriggered);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADLPlayerController::OnInputStarted()
{
	if (CachedPlayerCharacter != nullptr)
	{
		CachedPlayerCharacter->StopMovement();
	}
}

// Triggered every frame when the input is held down
void ADLPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	if (CurrentMouseHitType == EMouseHitType::Default_Walk && CachedPlayerCharacter != nullptr)
	{
		CachedPlayerCharacter->ApplyMovmentInputToTarget(CachedDestination);
	}
}

void ADLPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (CurrentMouseHitType == EMouseHitType::Default_Walk && FollowTime <= ShortPressThreshold && CachedPlayerCharacter != nullptr)
	{
		CachedPlayerCharacter->TriggerMoveToDestination(CachedDestination);
	}

	FollowTime = 0.f;
}

void ADLPlayerController::OnMouseScrollTriggered(const FInputActionValue& Value)
{
	if (CachedPlayerCharacter != nullptr)
	{
		CachedPlayerCharacter->ChangeCameraPosition(Value.Get<float>());
	}
}

void ADLPlayerController::OnMouseHitObjectChanged(AActor* SenderActor, EMouseHitType NewMouseHitType)
{
	switch (NewMouseHitType)
	{
	case EMouseHitType::Default_Walk:
		CurrentMouseCursor = EMouseCursor::Default;
		break;
	case EMouseHitType::Attackable:
		CurrentMouseCursor = EMouseCursor::Crosshairs;
		break;
	case EMouseHitType::Interactable:
		CurrentMouseCursor = EMouseCursor::GrabHand;
		break;
	}
	CurrentMouseHitType = NewMouseHitType;
}

void ADLPlayerController::OnDestroyedEventCallback(AActor* actor)
{
	MouseGlobalEvents->OnMouseHitRegisteredEvent.RemoveDynamic(this, &ADLPlayerController::OnMouseHitObjectChanged);
}
