// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DLCharacterAttributeSet.generated.h"

UCLASS()
class DEVILLITEMULTIPLAYER_API UDLCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	FGameplayAttributeData Health = 100.f;

	UPROPERTY()
	FGameplayAttributeData Resource = 100.f;
	
public:
	DL_ATTRIBUTE_ACCESSORS(UDLCharacterAttributeSet, Health)
	DL_ATTRIBUTE_ACCESSORS(UDLCharacterAttributeSet, Resource)
};
