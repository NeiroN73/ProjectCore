// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Service.h"
#include "Base/Tickable.h"
#include "Base/TweensTypes.h"
#include "TweensService.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UTweensService : public UService,
public ITickable
{
    GENERATED_BODY()

public:
    virtual void OnTick(float DeltaSeconds) override;
    
    FTweenBuilder CreateTween(
        float From,
        float To,
        float Duration,
        const TFunction<void(float)>& UpdateCallback);

    FTweenBuilder CreateMoveTween(
        AActor* Target, 
        const FVector& ToLocation, 
        float Duration);
    
    FTweenBuilder CreateRotateTween(
        AActor* Target, 
        const FRotator& ToRotation, 
        float Duration);
    
    FTweenBuilder CreateScaleTween(
        AActor* Target, 
        const FVector& ToScale, 
        float Duration);
    
    FTweenHandle CreatePhysicsTween(
        UPrimitiveComponent* Component,
        const FVector& ToLocation,
        float Duration,
        float Force,
        ETweenEaseType EaseType = ETweenEaseType::Linear,
        const TFunction<void()>& CompleteCallback = nullptr);
    
    void KillTween(const FTweenHandle& Handle);
    FTweenData FindTween(FGuid Guid);
    
private:
    TMap<FGuid, FTweenData> ActiveTweens;
};