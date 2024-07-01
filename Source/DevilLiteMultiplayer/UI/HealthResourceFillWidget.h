// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthResourceFillWidget.generated.h"

struct FGameplayAttribute;
class ADLCharacterBase;
class UProgressBar;
/**
 * 
 */
UCLASS()
class DEVILLITEMULTIPLAYER_API UHealthResourceFillWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitializeWithAttribute(ADLCharacterBase* Owner, FGameplayAttribute& ConnectingAttribute);
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	UProgressBar* FillProgressBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bIsHealthAttribute;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bIsResourceAttribute;

	ADLCharacterBase* OwnerCharacter;

	UFUNCTION()
	void OnAttributeVauleChanged();
};
