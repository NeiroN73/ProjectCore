// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Config.h"
#include "UObject/Object.h"
#include "LevelsConfig.generated.h"

UENUM()
enum class ELevelNames : uint8
{
	Gameplay  UMETA(DisplayName = "Gameplay Level"),
	EntryPoint UMETA(DisplayName = "Entry Point")
};

UCLASS()
class PROJECTCORERUNTIME_API ULevelsConfig : public UConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<ELevelNames, TSoftObjectPtr<UWorld>> LevelsByName;

	TSoftObjectPtr<UWorld> GetLevel(ELevelNames InName);
};
