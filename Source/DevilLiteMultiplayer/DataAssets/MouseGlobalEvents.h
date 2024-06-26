// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MouseGlobalEvents.generated.h"

UENUM(BlueprintType)
enum class EMouseHitType : uint8 {
    Default_Walk = 0 UMETA(DisplayName = "Default_Walk"),
    Interactable = 1  UMETA(DisplayName = "Interactable"),
    Attackable = 2     UMETA(DisplayName = "Attackable")
};

UCLASS()
class DEVILLITEMULTIPLAYER_API UMouseGlobalEvents : public UDataAsset
{
	GENERATED_BODY()
	
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMouseHitRegestered, AActor*, SenderActor, EMouseHitType, CurrentMouseHitType);
    UPROPERTY(VisibleAnywhere, BlueprintAssignable, BlueprintCallable)
    FOnMouseHitRegestered OnMouseHitRegisteredEvent;
};