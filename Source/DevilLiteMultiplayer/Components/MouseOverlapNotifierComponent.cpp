#include "MouseOverlapNotifierComponent.h"

void UMouseOverlapNotifierComponent::BeginPlay()
{
	Super::BeginPlay();

	if(MouseGlobalEvents != nullptr)
	{
		OnBeginCursorOver.AddDynamic(this, &UMouseOverlapNotifierComponent::BegunCursorOver);
		OnEndCursorOver.AddDynamic(this, &UMouseOverlapNotifierComponent::EndCursorOver);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The Mouse Global Events Data Asset is not assigned"));
	}
}

void UMouseOverlapNotifierComponent::BegunCursorOver(UPrimitiveComponent* Component)
{
	MouseGlobalEvents->OnMouseHitRegisteredEvent.Broadcast(GetOwner(), MouseHitType);
}

void UMouseOverlapNotifierComponent::EndCursorOver(UPrimitiveComponent* Component)
{
	MouseGlobalEvents->OnMouseHitRegisteredEvent.Broadcast(GetOwner(), EMouseHitType::Default_Walk);
}
