#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "DLPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UInputMappingContext;
class UInputAction;
class ADLPlayerCharacter;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class DEVILLITEMULTIPLAYER_API ADLPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADLPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Set Destination Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Set Destination Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MouseScrollAction;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnMouseScrollTriggered(const FInputActionValue& Value);

private:
	FVector CachedDestination;
	ADLPlayerCharacter* CachedPlayerCharacter;

	float FollowTime; // For how long it has been pressed
	const ECollisionChannel mouseRegesterableChannel = ECollisionChannel::ECC_GameTraceChannel1;
};
