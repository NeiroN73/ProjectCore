#include "TweensSubsystem.h"

TStatId UTweensSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UTweensSubsystem, STATGROUP_Tickables);
}

void UTweensSubsystem::Tick(float DeltaTime)
{
    TArray<FGuid> KeysToRemove;
    TArray<FSimpleDelegate> CallbacksToExecute;
    
    for (auto& [Guid, Tween] : ActiveTweens)
    {
        if (Tween.IsValid() && Tween.Get()->IsValid())
        {
            Tween->OnTick(DeltaTime);
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

bool UTweensSubsystem::IsTickable() const
{
    return !ActiveTweens.IsEmpty();
}

ETickableTickType UTweensSubsystem::GetTickableTickType() const
{
    return ETickableTickType::Conditional;
}

FFloatTweenBuilder UTweensSubsystem::CreateFloatTween(float From, float To, float Duration, FSimpleDelegate UpdateCallback)
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

FActorLocationTweenBuilder UTweensSubsystem::CreateMoveTween(AActor* Actor, const FVector& ToLocation, float Duration)
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

FActorRotateTweenBuilder UTweensSubsystem::CreateRotateTween(AActor* Actor, const FRotator& ToRotation, float Duration)
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

FActorScaleTweenBuilder UTweensSubsystem::CreateScaleTween(AActor* Actor, const FVector& ToScale, float Duration)
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

void UTweensSubsystem::KillTween(const FTweenHandle& Handle)
{
    if (auto Tween = ActiveTweens.Find(Handle.Guid))
    {
        Tween->Get()->Kill();
    }
    ActiveTweens.Remove(Handle.Guid);
}

bool UTweensSubsystem::IsTweening(const FTweenHandle& Handle)
{
    return ActiveTweens.Contains(Handle.Guid);
}
