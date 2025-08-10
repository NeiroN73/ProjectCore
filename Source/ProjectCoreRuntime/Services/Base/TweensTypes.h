#pragma once

#include "CoreMinimal.h"
#include "TweensTypes.generated.h"

UENUM()
enum class ETweenEaseType : uint8
{
    Linear,
    EaseIn,
    EaseOut,
    EaseInOut,
    CustomCurve
};

USTRUCT()
struct FTweenHandle
{
    GENERATED_BODY()
    
    FGuid Guid;
    
    bool IsValid() const { return Guid.IsValid(); }
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
    TWeakObjectPtr<UCurveFloat> CustomCurve = nullptr;
    TFunction<void()> CompleteCallback;
    bool bIsRunning = true;
    
    virtual void OnTick(float DeltaTime) PURE_VIRTUAL(FTweenBase::OnTick)
    
    bool IsComplete() const
    {
        if (Duration == -1)
        {
            return false;
        }
        return CurrentTime >= Duration;
    }

protected:
    float GetEasedAlpha() const
    {
        auto Alpha = Duration < 0 ? 1.0f : FMath::Clamp(CurrentTime / Duration, 0.f, 1.f);;
        switch(EaseType)
        {
            case ETweenEaseType::EaseIn: return FMath::InterpEaseIn(0.f, 1.f, Alpha, 2.f);
            case ETweenEaseType::EaseOut: return FMath::InterpEaseOut(0.f, 1.f, Alpha, 2.f);
            case ETweenEaseType::EaseInOut: return FMath::InterpEaseInOut(0.f, 1.f, Alpha, 2.f);
            case ETweenEaseType::CustomCurve: return CustomCurve.IsValid() ? CustomCurve->GetFloatValue(Alpha) : Alpha;
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
    TFunction<void(float)> UpdateCallback;

    virtual void OnTick(float DeltaTime) override
    {
        CurrentTime += DeltaTime;
        if (UpdateCallback) UpdateCallback(GetValue());
    }

    float GetValue() const
    {
        float EasedAlpha = GetEasedAlpha();
        return FMath::Lerp(StartValue, EndValue, EasedAlpha);
    }
};

USTRUCT()
struct FActorMoveTween : public FTweenBase
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

template<typename TweenType>
struct TTweenBuilder
{
    TTweenBuilder(TSharedPtr<TweenType> InTween) : Tween(InTween) {}
    
    TTweenBuilder& SetEaseType(ETweenEaseType Type)
    {
        Tween->EaseType = Type;
        return *this;
    }
    
    TTweenBuilder& SetCustomCurve(UCurveFloat* Curve)
    {
        Tween->CustomCurve = Curve;
        Tween->EaseType = ETweenEaseType::CustomCurve;
        return *this;
    }
    
    TTweenBuilder& OnComplete(TFunction<void()> Callback)
    {
        Tween->CompleteCallback = Callback;
        return *this;
    }
    
    FTweenHandle Build() { return Tween->Handle; }

protected:
    TSharedPtr<TweenType> Tween;
};

struct FFloatTweenBuilder : public TTweenBuilder<FFloatTween>
{
    FFloatTweenBuilder(TSharedPtr<FFloatTween> InTween) : TTweenBuilder(InTween) {}
    
    FFloatTweenBuilder& SetLoop(int32 Count, bool bPingPong = false)
    {
        // TODO: Implement loop logic
        return *this;
    }
};

struct FActorMoveTweenBuilder : public TTweenBuilder<FActorMoveTween>
{
    FActorMoveTweenBuilder(TSharedPtr<FActorMoveTween> InTween) : TTweenBuilder(InTween) {}
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

struct FPhysicsTweenBuilder : public TTweenBuilder<FPhysicsTween>
{
    FPhysicsTweenBuilder(TSharedPtr<FPhysicsTween> InTween) : TTweenBuilder(InTween) {}
    
    FPhysicsTweenBuilder& SetForce(float Force)
    {
        Tween->PhysicsForce = Force;
        return *this;
    }
};