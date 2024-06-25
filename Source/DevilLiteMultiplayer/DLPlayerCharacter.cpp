#include "DLPlayerCharacter.h"
#include "NiagaraSystem.h"
#include "GameFramework/SpringArmComponent.h"
#include "NiagaraFunctionLibrary.h"

void ADLPlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (bIsCameraLerping)
	{
        CameraLerpTimer += DeltaSeconds;
        float lerpValue = CameraLerpTimer / CameraLerpTime;
        if (lerpValue >= 1.f)
        {
            lerpValue = 1.f;
            CameraLerpTimer = 0.f;
            bIsCameraLerping = false;
        }
        CameraBoom->TargetArmLength = FMath::Lerp(SpringArmLerpEndPoints.X, SpringArmLerpEndPoints.Y, lerpValue);
	}
}

void ADLPlayerCharacter::ChangeCameraPosition(const float& inputValue)
{
    if (inputValue > 0.2f)
    {
        SetCameraLerpTarget(SpringArmLengthMinMax.Y, SpringArmLengthMinMax.X);
    }
    else if (inputValue < -0.2f)
    {
		SetCameraLerpTarget(SpringArmLengthMinMax.X, SpringArmLengthMinMax.Y);
    }
}

void ADLPlayerCharacter::SetCameraLerpTarget(const float& targetStart, const float& targetEnd)
{
	if (SpringArmLerpEndPoints.Y != targetEnd)
	{
		SpringArmLerpEndPoints = FVector2D(targetStart, targetEnd);
        if (CameraLerpTimer != 0.f)
        {
		    CameraLerpTimer = CameraLerpTime - CameraLerpTimer;
        }
		bIsCameraLerping = true;
	}
}

void ADLPlayerCharacter::TriggerMoveToDestination(const FVector& TargetLocation)
{
	Super::TriggerMoveToDestination(TargetLocation);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, TargetLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}
