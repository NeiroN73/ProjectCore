#pragma once

#include "CoreMinimal.h"
#include "Base/TweensTypes.h"
#include "TweensSubsystem.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UTweensSubsystem : public UTickableWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual TStatId GetStatId() const override;
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;
    virtual ETickableTickType GetTickableTickType() const override;
    
    FFloatTweenBuilder CreateFloatTween(float From, float To, float Duration, FSimpleDelegate UpdateCallback);
    FActorLocationTweenBuilder CreateMoveTween(AActor* Actor, const FVector& ToLocation, float Duration);
    FActorRotateTweenBuilder CreateRotateTween(AActor* Actor, const FRotator& ToRotation, float Duration);
    FActorScaleTweenBuilder CreateScaleTween(AActor* Actor, const FVector& ToScale, float Duration);
    
    void KillTween(const FTweenHandle& Handle);
    bool IsTweening(const FTweenHandle& Handle);

private:
    TMap<FGuid, TSharedPtr<FTweenBase>> ActiveTweens;
};