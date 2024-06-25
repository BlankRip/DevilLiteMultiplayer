// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DevilLiteMultiplayerCharacter.h"
#include "DLPlayerCharacter.generated.h"


class UNiagaraSystem;

UCLASS()
class DEVILLITEMULTIPLAYER_API ADLPlayerCharacter : public ADevilLiteMultiplayerCharacter
{
	GENERATED_BODY()
	
public:
	void ChangeCameraPosition(const float& inputValue);

	void TriggerMoveToDestination(const FVector& TargetLocation) override;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;
};
