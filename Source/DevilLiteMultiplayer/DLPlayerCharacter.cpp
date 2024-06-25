#include "DLPlayerCharacter.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

void ADLPlayerCharacter::ChangeCameraPosition(const float& inputValue)
{
}

void ADLPlayerCharacter::TriggerMoveToDestination(const FVector& TargetLocation)
{
	Super::TriggerMoveToDestination(TargetLocation);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, TargetLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}
