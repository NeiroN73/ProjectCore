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
    
    FFloatTweenBuilder CreateFloatTween(float From, float To, float Duration, FSimpleDelegate UpdateCallback);
    FActorLocationTweenBuilder CreateMoveTween(AActor* Actor, const FVector& ToLocation, float Duration);
    FActorRotateTweenBuilder CreateRotateTween(AActor* Actor, const FRotator& ToRotation, float Duration);
    FActorScaleTweenBuilder CreateScaleTween(AActor* Actor, const FVector& ToScale, float Duration);
    
    void KillTween(const FTweenHandle& Handle);
    bool IsTweening(const FTweenHandle& Handle);

private:
    TMap<FGuid, TSharedPtr<FTweenBase>> ActiveTweens;
};