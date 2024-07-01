// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthResourceFillWidget.h"

#include "AttributeSet.h"
#include "Components/ProgressBar.h"
#include "DevilLiteMultiplayer/Character/DLCharacterBase.h"

void UHealthResourceFillWidget::InitializeWithAttribute(ADLCharacterBase* Owner, FGameplayAttribute& ConnectingAttribute)
{
	OwnerCharacter = Owner;
}

void UHealthResourceFillWidget::OnAttributeVauleChanged()
{
	float fillAmount = 1.f;
	if(bIsHealthAttribute)
	{
		fillAmount = OwnerCharacter->GetNormalizedHealthValue();
	}
	else if(bIsResourceAttribute)
	{
		fillAmount = OwnerCharacter->GetNormalizedResourceValue();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("None of the the health or resource bools are ticked on this User widget"));
	}
	FillProgressBar->SetPercent(fillAmount);
}
