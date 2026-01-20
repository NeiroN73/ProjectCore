#include "TweensService.h"

void UTweensService::OnTick(float DeltaSeconds)
{
    TArray<FGuid> KeysToRemove;
    TArray<FSimpleDelegate> CallbacksToExecute;
    
    for (auto& [Guid, Tween] : ActiveTweens)
    {
        if (Tween.IsValid() && Tween.Get()->IsValid())
        {
            Tween->OnTick(DeltaSeconds);
            if (Tween->IsComplete())
            {
                if (Tween->CompleteCallback.IsBound())
                {
                    CallbacksToExecute.Add(Tween->CompleteCallback);
                }
                KeysToRemove.Add(Guid);
            }
        }
        else
        {
            KeysToRemove.Add(Guid);
        }
    }

    for (auto& Callback : CallbacksToExecute)
    {
        Callback.ExecuteIfBound();
    }

    for (const FGuid& Key : KeysToRemove)
    {
        ActiveTweens.Remove(Key);
    }
}

FFloatTweenBuilder UTweensService::CreateFloatTween(float From, float To, float Duration, FSimpleDelegate UpdateCallback)
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

FActorLocationTweenBuilder UTweensService::CreateMoveTween(AActor* Actor, const FVector& ToLocation, float Duration)
{
    auto Tween = MakeShared<FActorLocationTween>();
    Tween->Handle.Guid = FGuid::NewGuid();
    Tween->Actor = Actor;
    Tween->StartLocation = Actor ? Actor->GetActorLocation() : FVector::ZeroVector;
    Tween->EndLocation = ToLocation;
    Tween->Duration = Duration;
    
    ActiveTweens.Add(Tween->Handle.Guid, Tween);
    return FActorLocationTweenBuilder(Tween);
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

void UTweensService::KillTween(const FTweenHandle& Handle)
{
    if (auto Tween = ActiveTweens.Find(Handle.Guid))
    {
        Tween->Get()->Kill();
    }
    ActiveTweens.Remove(Handle.Guid);
}

bool UTweensService::IsTweening(const FTweenHandle& Handle)
{
    return ActiveTweens.Contains(Handle.Guid);
}
