// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#include "TweensService.h"

void UTweensService::OnTick(float DeltaSeconds)
{
    for (auto [Guid, Tween] : ActiveTweens)
    {
        if (!Tween.bIsRunning)
            continue;
            
        Tween.CurrentTime += DeltaSeconds;
        
        if (Tween.bUsePhysics)
        {
            if (Tween.TargetComponent.IsValid())
            {
                const float Alpha = FMath::Clamp(Tween.CurrentTime / Tween.Duration, 0.f, 1.f);
                const FVector CurrentLocation = FMath::Lerp(Tween.StartLocation, Tween.EndLocation, Alpha);
                const FVector Direction = (Tween.EndLocation - Tween.TargetComponent->GetComponentLocation()).GetSafeNormal();
                Tween.TargetComponent->AddForce(Direction * Tween.PhysicsForce);
            }
        }
        else if (Tween.UpdateCallback)
        {
            Tween.UpdateCallback(Tween.GetValue());
        }
        
        if (Tween.CurrentTime >= Tween.Duration)
        {
            if (Tween.CompleteCallback)
                Tween.CompleteCallback();
            ActiveTweens.Remove(Guid);
        }
    }
}

FTweenBuilder UTweensService::CreateTween(float From, float To, float Duration,
    const TFunction<void(float)>& UpdateCallback)
{
    FTweenData NewTween;
    NewTween.Handle.Guid = FGuid::NewGuid();
    NewTween.StartValue = From;
    NewTween.EndValue = To;
    NewTween.Duration = Duration;
    NewTween.UpdateCallback = UpdateCallback;
    
    ActiveTweens.Add(NewTween.Handle.Guid, NewTween);

    FTweenBuilder Builder = FTweenBuilder(NewTween.Handle.Guid, NewTween);
    return Builder;
}

FTweenBuilder UTweensService::CreateMoveTween(AActor* Target, const FVector& ToLocation, float Duration)
{
    if (!Target)
    {
        return FTweenBuilder();
    }

    FTweenData NewTween;
    NewTween.Handle.Guid = FGuid::NewGuid();
    NewTween.StartLocation = Target->GetActorLocation();
    NewTween.EndLocation = ToLocation;
    NewTween.Duration = Duration;
    
    NewTween.UpdateCallback = [Target, NewTween](float Alpha) {
        if (Target)
        {
            Target->SetActorLocation(FMath::Lerp(NewTween.StartLocation, NewTween.EndLocation, Alpha));
        }
    };
    
    ActiveTweens.Add(NewTween.Handle.Guid, NewTween);

    FTweenBuilder Builder = FTweenBuilder(NewTween.Handle.Guid, NewTween);
    return Builder;
}

FTweenBuilder UTweensService::CreateRotateTween(AActor* Target, const FRotator& ToRotation, float Duration)
{
    if (!Target)
    {
        return FTweenBuilder();
    }

    FTweenData NewTween;
    NewTween.Handle.Guid = FGuid::NewGuid();
    NewTween.StartValue = 0.0f;
    NewTween.EndValue = 1.0f;
    NewTween.Duration = Duration;
    
    const FRotator StartRotation = Target->GetActorRotation();
    TWeakObjectPtr<AActor> TargetPtr = Target;
    
    NewTween.UpdateCallback = [TargetPtr, StartRotation, ToRotation](float Alpha) {
        if (TargetPtr.IsValid())
        {
            FRotator NewRotation = FMath::Lerp(StartRotation, ToRotation, Alpha);
            TargetPtr->SetActorRotation(NewRotation);
        }
    };
    
    ActiveTweens.Add(NewTween.Handle.Guid, NewTween);

    FTweenBuilder Builder = FTweenBuilder(NewTween.Handle.Guid, NewTween);
    return Builder;
}

FTweenBuilder UTweensService::CreateScaleTween(AActor* Target, const FVector& ToScale, float Duration)
{
    if (!Target)
    {
        return FTweenBuilder();
    }

    FTweenData NewTween;
    NewTween.Handle.Guid = FGuid::NewGuid();
    NewTween.StartValue = 0.0f;
    NewTween.EndValue = 1.0f;
    NewTween.Duration = Duration;
    
    const FVector StartScale = Target->GetActorScale();
    TWeakObjectPtr<AActor> TargetPtr = Target;
    
    NewTween.UpdateCallback = [TargetPtr, StartScale, ToScale](float Alpha) {
        if (TargetPtr.IsValid())
        {
            FVector NewScale = FMath::Lerp(StartScale, ToScale, Alpha);
            TargetPtr->SetActorScale3D(NewScale);
        }
    };
    
    ActiveTweens.Add(NewTween.Handle.Guid, NewTween);

    FTweenBuilder Builder = FTweenBuilder(NewTween.Handle.Guid, NewTween);
    return Builder;
}

FTweenHandle UTweensService::CreatePhysicsTween(
    UPrimitiveComponent* Component,
    const FVector& ToLocation,
    float Duration,
    float Force,
    ETweenEaseType EaseType,
    const TFunction<void()>& CompleteCallback)
{
    if (!Component || !Component->IsSimulatingPhysics())
    {
        return FTweenHandle();
    }

    FTweenData NewTween;
    NewTween.Handle.Guid = FGuid::NewGuid();
    NewTween.StartLocation = Component->GetComponentLocation();
    NewTween.EndLocation = ToLocation;
    NewTween.Duration = Duration;
    NewTween.EaseType = EaseType;
    NewTween.bUsePhysics = true;
    NewTween.PhysicsForce = Force;
    NewTween.TargetComponent = Component;
    NewTween.CompleteCallback = CompleteCallback;

    ActiveTweens.Add(NewTween.Handle.Guid, NewTween);
    return NewTween.Handle;
}

void UTweensService::KillTween(const FTweenHandle& Handle)
{
    ActiveTweens.Remove(Handle.Guid);
}

FTweenData UTweensService::FindTween(FGuid Guid)
{
    if (auto Tween = ActiveTweens.Find(Guid))
    {
        return *Tween;
    }
    return FTweenData();
}
