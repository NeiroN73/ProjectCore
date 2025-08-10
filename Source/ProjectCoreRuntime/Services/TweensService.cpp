#include "TweensService.h"

void UTweensService::OnTick(float DeltaSeconds)
{
    for (auto It = ActiveTweens.CreateIterator(); It; ++It)
    {
        auto& Tween = It->Value;
        if (Tween->bIsRunning)
        {
            Tween->OnTick(DeltaSeconds);
            if (Tween->IsComplete())
            {
                if (Tween->CompleteCallback)
                    Tween->CompleteCallback();
                
                It.RemoveCurrent();
            }
        }
    }
}

FFloatTweenBuilder UTweensService::CreateFloatTween(float From, float To, float Duration, TFunction<void(float)> UpdateCallback)
{
    auto Tween = MakeShared<FFloatTween>();
    Tween->Handle.Guid = FGuid::NewGuid();
    Tween->StartValue = From;
    Tween->EndValue = To;
    Tween->Duration = Duration;
    Tween->UpdateCallback = UpdateCallback;
    
    ActiveTweens.Add(Tween->Handle.Guid, Tween);
    return FFloatTweenBuilder(Tween);
}

FActorMoveTweenBuilder UTweensService::CreateMoveTween(AActor* Actor, const FVector& ToLocation, float Duration)
{
    auto Tween = MakeShared<FActorMoveTween>();
    Tween->Handle.Guid = FGuid::NewGuid();
    Tween->Actor = Actor;
    Tween->StartLocation = Actor ? Actor->GetActorLocation() : FVector::ZeroVector;
    Tween->EndLocation = ToLocation;
    Tween->Duration = Duration;
    
    ActiveTweens.Add(Tween->Handle.Guid, Tween);
    return FActorMoveTweenBuilder(Tween);
}

FActorTransformTweenBuilder UTweensService::CreateFollowTween(AActor* Actor, USceneComponent* Target, float Duration,
    float Speed)
{
    auto Tween = MakeShared<FActorTransformTween>();
    Tween->Handle.Guid = FGuid::NewGuid();
    Tween->Actor = Actor;
    Tween->TargetComponent = Target;
    Tween->Duration = Duration;
    Tween->Speed = Speed;
    
    ActiveTweens.Add(Tween->Handle.Guid, Tween);
    return FActorTransformTweenBuilder(Tween);
}

FActorRotateTweenBuilder UTweensService::CreateRotateTween(AActor* Actor, const FRotator& ToRotation, float Duration)
{
    auto Tween = MakeShared<FActorRotateTween>();
    Tween->Handle.Guid = FGuid::NewGuid();
    Tween->Actor = Actor;
    Tween->StartRotation = Actor ? Actor->GetActorRotation() : FRotator::ZeroRotator;
    Tween->EndRotation = ToRotation;
    Tween->Duration = Duration;
    
    ActiveTweens.Add(Tween->Handle.Guid, Tween);
    return FActorRotateTweenBuilder(Tween);
}

FActorScaleTweenBuilder UTweensService::CreateScaleTween(AActor* Actor, const FVector& ToScale, float Duration)
{
    auto Tween = MakeShared<FActorScaleTween>();
    Tween->Handle.Guid = FGuid::NewGuid();
    Tween->Actor = Actor;
    Tween->StartScale = Actor ? Actor->GetActorScale3D() : FVector::OneVector;
    Tween->EndScale = ToScale;
    Tween->Duration = Duration;
    
    ActiveTweens.Add(Tween->Handle.Guid, Tween);
    return FActorScaleTweenBuilder(Tween);
}

FPhysicsTweenBuilder UTweensService::CreatePhysicsTween(UPrimitiveComponent* Component, const FVector& ToLocation, float Duration, float Force)
{
    auto Tween = MakeShared<FPhysicsTween>();
    Tween->Handle.Guid = FGuid::NewGuid();
    Tween->Component = Component;
    Tween->StartLocation = Component ? Component->GetComponentLocation() : FVector::ZeroVector;
    Tween->EndLocation = ToLocation;
    Tween->Duration = Duration;
    Tween->PhysicsForce = Force;
    
    ActiveTweens.Add(Tween->Handle.Guid, Tween);
    return FPhysicsTweenBuilder(Tween);
}

void UTweensService::KillTween(const FTweenHandle& Handle)
{
    ActiveTweens.Remove(Handle.Guid);
}