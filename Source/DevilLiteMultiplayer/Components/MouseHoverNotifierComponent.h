// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MouseHoverNotifierComponent.generated.h"

class UMouseHoverGlobalEvent;
UCLASS()
class DEVILLITEMULTIPLAYER_API AMouseHoverNotifierComponent : public ATriggerBox
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UMouseHoverGlobalEvent* MouseHoverGloablEvent;
};
