// Copyright Epic Games, Inc. All Rights Reserved.

#include "DLCharacterBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ADLCharacterBase::ADLCharacterBase()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	//Creating ability system component
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System"));
	AttributeSet = CreateDefaultSubobject<UDLCharacterAttributeSet>(TEXT("Attribute Set"));
}

void ADLCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystem->InitAbilityActorInfo(this, this);
	AttributeSet->InitResource(BaseResource);
	AttributeSet->InitHealth(BaseHealth);
}

void ADLCharacterBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
	if(GEngine)
	{
		FString LvalueToPrintStr = FString::SanitizeFloat(AttributeSet->GetResourceAttribute().GetGameplayAttributeData(AttributeSet)->GetCurrentValue());
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Purple, TEXT(valueToPrintStr));
		FString LvalueToPrintStr2 = FString::SanitizeFloat(AttributeSet->GetResourceAttribute().GetGameplayAttributeData(AttributeSet)->GetBaseValue());
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Purple, TEXT(valueToPrintStr2));
	}
}

void ADLCharacterBase::StopMovement()
{
	GetController()->StopMovement();
}

void ADLCharacterBase::ApplyMovmentInputToTarget(const FVector& TargetLoction)
{
	FVector WorldDirection = (TargetLoction - GetActorLocation()).GetSafeNormal();
	AddMovementInput(WorldDirection, 1.0, false);
}

void ADLCharacterBase::TriggerMoveToDestination(const FVector& TargetLocation)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), TargetLocation);
}
