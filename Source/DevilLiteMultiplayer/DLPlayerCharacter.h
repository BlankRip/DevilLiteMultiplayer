// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DLCharacterBase.h"
#include "DLPlayerCharacter.generated.h"


class UNiagaraSystem;

UCLASS()
class DEVILLITEMULTIPLAYER_API ADLPlayerCharacter : public ADLCharacterBase
{
	GENERATED_BODY()
	
public:
	ADLPlayerCharacter();

	void Tick(float DeltaSeconds) override;

	void ChangeCameraPosition(const float& inputValue);

	void TriggerMoveToDestination(const FVector& TargetLocation) override;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Effects")
	UNiagaraSystem* FXCursor;

private:
	void SetCameraLerpTarget(const float& targetStart, const float& targetEnd);

	bool bIsCameraLerping;
	FVector2D SpringArmLerpEndPoints;
	float CameraLerpTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Effects", meta = (AllowPrivateAccess = "true"))
	float CameraLerpTime = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Effects", meta = (AllowPrivateAccess = "true"))
	FVector2D SpringArmLengthMinMax = FVector2D(800.f, 1400.f);
};
