#include "MouseOverlapNotifierComponent.h"

void UMouseOverlapNotifierComponent::BeginPlay()
{
	Super::BeginPlay();

	ensureAlwaysMsgf(MouseGlobalEvents != nullptr, TEXT("The Mouse Global Events Data Asset is not assigned on mouse overlap notifier componet of actor %s"), *GetOwner()->GetName());
	if(MouseGlobalEvents != nullptr)
	{
		OnBeginCursorOver.AddDynamic(this, &UMouseOverlapNotifierComponent::BegunCursorOver);
		OnEndCursorOver.AddDynamic(this, &UMouseOverlapNotifierComponent::EndCursorOver);
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
