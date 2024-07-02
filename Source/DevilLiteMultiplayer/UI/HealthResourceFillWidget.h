// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
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
	void InitializeWithAttribute(ADLCharacterBase* OwnerChar, const FGameplayAttribute& ConnectingAttribute);
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true, BindWidget))
	UProgressBar* FillProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bIsHealthAttribute;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bIsResourceAttribute;

	ADLCharacterBase* OwnerCharacter;

	void OnAttributeVauleChanged(const FOnAttributeChangeData& AttributeChangeData);
};
