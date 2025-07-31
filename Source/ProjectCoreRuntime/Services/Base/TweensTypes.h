// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

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
    
    bool IsValid() const
    {
        return Guid.IsValid();
    }
};

USTRUCT()
struct FTweenData
{
    GENERATED_BODY()
    
    FTweenHandle Handle;
    float CurrentTime = 0.f;
    float Duration = 0.f;
    float StartValue = 0.f;
    float EndValue = 0.f;
    ETweenEaseType EaseType = ETweenEaseType::Linear;
    UPROPERTY()
    TWeakObjectPtr<UCurveFloat> CustomCurve = nullptr;
    TFunction<void(float)> UpdateCallback;
    TFunction<void()> CompleteCallback;
    bool bIsRunning = true;
    UPROPERTY()
    TWeakObjectPtr<UPrimitiveComponent> TargetComponent;
    FVector StartLocation;
    FVector EndLocation;
    bool bUsePhysics = false;
    float PhysicsForce = 1000.0f;
    
    float GetValue() const
    {
        const float Alpha = FMath::Clamp(CurrentTime / Duration, 0.f, 1.f);
        float EasedAlpha = Alpha;
        
        switch(EaseType)
        {
        case ETweenEaseType::EaseIn:
            EasedAlpha = FMath::InterpEaseIn(0.f, 1.f, Alpha, 2.f);
            break;
        case ETweenEaseType::EaseOut:
            EasedAlpha = FMath::InterpEaseOut(0.f, 1.f, Alpha, 2.f);
            break;
        case ETweenEaseType::EaseInOut:
            EasedAlpha = FMath::InterpEaseInOut(0.f, 1.f, Alpha, 2.f);
            break;
        case ETweenEaseType::CustomCurve:
            if(CustomCurve.Get())
            {
                EasedAlpha = CustomCurve->GetFloatValue(Alpha);
            }
            break;
        default:
            break;
        }

        return FMath::Lerp(StartValue, EndValue, EasedAlpha);
    }
};

USTRUCT()
struct FTweenBuilder
{
    GENERATED_BODY()

    FTweenBuilder() = default;
    
    FTweenBuilder(FGuid InTweenGuid, FTweenData InTweenData) :
    TweenGuid(InTweenGuid), TweenData(InTweenData)
    {
    }

private:
    FGuid TweenGuid;
    FTweenData TweenData;
    
public:
    FTweenBuilder& SetEaseType(ETweenEaseType Type)
    {
        TweenData.EaseType = Type;
        
        return *this;
    }
    
    FTweenBuilder& SetCustomCurve(UCurveFloat* Curve)
    {
        TweenData.CustomCurve = Curve;
        TweenData.EaseType = ETweenEaseType::CustomCurve;
        
        return *this;
    }
    
    FTweenBuilder& SetLoop(int32 Count, bool bInPingPong = false)
    {
        TweenData.CurrentTime = 0.f;
        return *this;
    }
    
    FTweenBuilder& OnComplete(TFunction<void()> Callback)
    {
        TweenData.CompleteCallback = Callback;
        return *this;
    }
    
    FTweenHandle Build() const
    {
        return FTweenHandle{TweenGuid};
    }
};
