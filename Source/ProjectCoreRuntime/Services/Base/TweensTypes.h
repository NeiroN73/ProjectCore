#pragma once

#include "CoreMinimal.h"
#include "TweensTypes.generated.h"

UENUM()
enum class ETweenEaseType : uint8
{
    Linear,
    EasySinIn,
    EasySinOut,
    EasySinInOut
};

USTRUCT()
struct FTweenHandle
{
    GENERATED_BODY()
    
    FGuid Guid;
};

USTRUCT()
struct FTweenBase
{
    GENERATED_BODY()
    
    virtual ~FTweenBase() = default;
    
    FTweenHandle Handle;
    float CurrentTime = 0.f;
    float Duration = 0.f;
    ETweenEaseType EaseType = ETweenEaseType::Linear;
    FSimpleDelegate CompleteCallback;
    
    virtual void OnTick(float DeltaTime) PURE_VIRTUAL(FTweenBase::OnTick)
    
    bool IsComplete() const
    {
        if (Duration == -1)
        {
            return false;
        }
        return CurrentTime >= Duration;
    }

    void Reset()
    {
        CurrentTime = Duration;
    }

    void Kill()
    {
        Handle.Guid.Invalidate();
    }

    bool IsValid() const
    {
        return Handle.Guid.IsValid();
    }

protected:
    float GetEasedAlpha() const
    {
        auto Alpha = Duration < 0 ? 1.0f : FMath::Clamp(CurrentTime / Duration, 0.f, 1.f);
        switch(EaseType)
        {
            case ETweenEaseType::EasySinIn: return FMath::InterpSinIn(0.f, 1.f, Alpha);
            case ETweenEaseType::EasySinOut: return FMath::InterpSinOut(0.f, 1.f, Alpha);
            case ETweenEaseType::EasySinInOut: return FMath::InterpSinInOut(0.f, 1.f, Alpha);
            default: return Alpha;
        }
    }
};

USTRUCT()
struct FFloatTween : public FTweenBase
{
    GENERATED_BODY()

    float StartValue = 0.f;
    float EndValue = 0.f;
    FSimpleDelegate UpdateCallback;

    virtual void OnTick(float DeltaTime) override
    {
        CurrentTime += DeltaTime;
        UpdateCallback.ExecuteIfBound();
    }

    float GetValue() const
    {
        float EasedAlpha = GetEasedAlpha();
        return FMath::Lerp(StartValue, EndValue, EasedAlpha);
    }
};

USTRUCT()
struct FActorLocationTween : public FTweenBase
{
    GENERATED_BODY()

    TWeakObjectPtr<AActor> Actor;
    FVector StartLocation;
    FVector EndLocation;

    virtual void OnTick(float DeltaTime) override
    {
        CurrentTime += DeltaTime;
        if (Actor.IsValid())
        {
            const float EasedAlpha = GetEasedAlpha();
            Actor->SetActorLocation(FMath::Lerp(StartLocation, EndLocation, EasedAlpha));
        }
    }
};

USTRUCT()
struct FActorTransformTween : public FTweenBase
{
    GENERATED_BODY()

    TWeakObjectPtr<AActor> Actor;
    UPROPERTY()
    USceneComponent* TargetComponent;
    float Speed;

    virtual void OnTick(float DeltaTime) override
    {
        CurrentTime += DeltaTime;
        if (Actor.IsValid())
        {
            const float EasedAlpha = GetEasedAlpha();
            Actor->SetActorLocation(FMath::Lerp(Actor->GetActorLocation(), TargetComponent->GetComponentLocation(), EasedAlpha));
        }
    }
};

USTRUCT()
struct FActorRotateTween : public FTweenBase
{
    GENERATED_BODY()

    TWeakObjectPtr<AActor> Actor;
    FRotator StartRotation;
    FRotator EndRotation;

    virtual void OnTick(float DeltaTime) override
    {
        CurrentTime += DeltaTime;
        if (Actor.IsValid())
        {
            const float EasedAlpha = GetEasedAlpha();
            Actor->SetActorRotation(FMath::Lerp(StartRotation, EndRotation, EasedAlpha));
        }
    }
};

USTRUCT()
struct FActorScaleTween : public FTweenBase
{
    GENERATED_BODY()

    TWeakObjectPtr<AActor> Actor;
    FVector StartScale;
    FVector EndScale;

    virtual void OnTick(float DeltaTime) override
    {
        CurrentTime += DeltaTime;
        if (Actor.IsValid())
        {
            const float EasedAlpha = GetEasedAlpha();
            Actor->SetActorScale3D(FMath::Lerp(StartScale, EndScale, EasedAlpha));
        }
    }
};

USTRUCT()
struct FPhysicsTween : public FTweenBase
{
    GENERATED_BODY()

    TWeakObjectPtr<UPrimitiveComponent> Component;
    FVector StartLocation;
    FVector EndLocation;
    float PhysicsForce = 1000.0f;

    virtual void OnTick(float DeltaTime) override
    {
        CurrentTime += DeltaTime;
        if (Component.IsValid() && Component->IsSimulatingPhysics())
        {
            const FVector Direction = (EndLocation - Component->GetComponentLocation()).GetSafeNormal();
            Component->AddForce(Direction * PhysicsForce);
        }
    }
};

template<typename TTween>
struct TTweenBuilder
{
    TTweenBuilder(TSharedPtr<TTween> InTween) : Tween(InTween) {}
    
    TTweenBuilder& SetEaseType(ETweenEaseType Type)
    {
        Tween->EaseType = Type;
        return *this;
    }
    
    TTweenBuilder& OnComplete(FSimpleDelegate Callback)
    {
        Tween->CompleteCallback = Callback;
        return *this;
    }
    
    FTweenHandle Build() { return Tween->Handle; }

protected:
    TSharedPtr<TTween> Tween;
};

struct FFloatTweenBuilder : public TTweenBuilder<FFloatTween>
{
    FFloatTweenBuilder(TSharedPtr<FFloatTween> InTween) : TTweenBuilder(InTween) {}
    
    FFloatTweenBuilder& SetLoop(int32 Count, bool bPingPong = false)
    {
        //todo: Implement loop logic
        return *this;
    }
};

struct FActorMoveTweenBuilder : public TTweenBuilder<FActorLocationTween>
{
    FActorMoveTweenBuilder(TSharedPtr<FActorLocationTween> InTween) : TTweenBuilder(InTween) {}
};

struct FActorRotateTweenBuilder : public TTweenBuilder<FActorRotateTween>
{
    FActorRotateTweenBuilder(TSharedPtr<FActorRotateTween> InTween) : TTweenBuilder(InTween) {}
};

struct FActorScaleTweenBuilder : public TTweenBuilder<FActorScaleTween>
{
    FActorScaleTweenBuilder(TSharedPtr<FActorScaleTween> InTween) : TTweenBuilder(InTween) {}
};

struct FActorTransformTweenBuilder : public TTweenBuilder<FActorTransformTween>
{
    FActorTransformTweenBuilder(TSharedPtr<FActorTransformTween> InTween) : TTweenBuilder(InTween) {}
};