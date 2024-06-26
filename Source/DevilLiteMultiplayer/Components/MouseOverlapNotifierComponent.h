// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DevilLiteMultiplayer/DataAssets/MouseGlobalEvents.h"
#include "MouseOverlapNotifierComponent.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class DEVILLITEMULTIPLAYER_API UMouseOverlapNotifierComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	EMouseHitType MouseHitType;
	UPROPERTY(EditDefaultsOnly)
	UMouseGlobalEvents* MouseGlobalEvents;

	UFUNCTION()
	void BegunCursorOver(UPrimitiveComponent* Component);
	UFUNCTION()
	void EndCursorOver(UPrimitiveComponent* Component);
};
