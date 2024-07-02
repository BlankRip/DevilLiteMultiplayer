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

	UFUNCTION(BlueprintCallable)
	FGameplayAttribute GetHealthAttribute();
	UFUNCTION(BlueprintCallable)
	FGameplayAttribute GetResourceAttribute();
	UFUNCTION(BlueprintCallable)
	float GetNormalizedHealthValue();
	UFUNCTION(BlueprintCallable)
	float GetNormalizedResourceValue();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetHealthRegenPerSecond(const float& ValueToSet) { HealthRegenPerSecond = ValueToSet; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void AddToHealthRegenPerSecond(const float& AddAmount) { HealthRegenPerSecond += AddAmount; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetResourceRegenPerSecond(const float& ValueToSet) { ResourceRegenPerSecond = ValueToSet; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void AddToResourceRegenPerSecond(const float& AddAmount) { ResourceRegenPerSecond += AddAmount; }

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribue Base Values", meta=(AllowPrivateAccess=true))
	float DefaultHealthRegenPerSecond = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribue Base Values", meta=(AllowPrivateAccess=true))
	float DefaultResourceRegenPerSecond = 5.f;

	UFUNCTION(BlueprintCallable)
	void HandleHealthRegenPerSecond(const float& DeltaSeconds);
	UFUNCTION(BlueprintCallable)
	void HandleResourceRegenPerSecond(const float& DeltaSeconds);

private:
	float HealthRegenPerSecond = 0.f;
	float ResourceRegenPerSecond = 0.f;

	void HandleHealthOrResourceRegenPerSecond(const float& DeltaSeconds, bool IsForHealth, const float& RegenPerSecondAmount, const float& BaseValue);
};

