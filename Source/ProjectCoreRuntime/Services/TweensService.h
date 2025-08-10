#pragma once

#include "CoreMinimal.h"
#include "Base/Service.h"
#include "Base/Tickable.h"
#include "Base/TweensTypes.h"
#include "TweensService.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UTweensService : public UService, public ITickable
{
    GENERATED_BODY()

public:
    virtual void OnTick(float DeltaSeconds) override;
    
    FFloatTweenBuilder CreateFloatTween(float From, float To, float Duration, TFunction<void(float)> UpdateCallback);
    FActorMoveTweenBuilder CreateMoveTween(AActor* Actor, const FVector& ToLocation, float Duration);
    FActorTransformTweenBuilder CreateFollowTween(AActor* Actor, USceneComponent* Target, float Duration, float Speed);
    FActorRotateTweenBuilder CreateRotateTween(AActor* Actor, const FRotator& ToRotation, float Duration);
    FActorScaleTweenBuilder CreateScaleTween(AActor* Actor, const FVector& ToScale, float Duration);
    FPhysicsTweenBuilder CreatePhysicsTween(UPrimitiveComponent* Component, const FVector& ToLocation, float Duration, float Force);
    
    void KillTween(const FTweenHandle& Handle);

private:
    TMap<FGuid, TSharedPtr<FTweenBase>> ActiveTweens;
};