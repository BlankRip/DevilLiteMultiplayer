// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "DevilLiteMultiplayer/AbilitySystem/Attributes/DLCharacterAttributeSet.h"
#include "DLCharacterBase.generated.h"

UCLASS(Blueprintable)
class ADLCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ADLCharacterBase();

	virtual void BeginPlay() override;
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; }

	void StopMovement();
	void ApplyMovmentInputToTarget(const FVector& TargetLoction);
	virtual void TriggerMoveToDestination(const FVector& TargetLocation);


protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystem;

	UPROPERTY()
	UDLCharacterAttributeSet* AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribue Base Values", meta=(AllowPrivateAccess=true))
	float BaseHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribue Base Values", meta=(AllowPrivateAccess=true))
	float BaseResource = 100.f;
};

