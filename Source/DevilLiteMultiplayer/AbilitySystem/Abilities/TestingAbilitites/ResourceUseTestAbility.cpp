// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceUseTestAbility.h"

#include "AbilitySystemComponent.h"
#include "DevilLiteMultiplayer/AbilitySystem/Attributes/DLCharacterAttributeSet.h"

void UResourceUseTestAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CommitAbility(Handle, ActorInfo, ActivationInfo);
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Firing Rapid Arrows"));
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
