// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "LevelsSubsystem.generated.h"

class UAssetsSubsystem;
class ULevelsConfig;

UCLASS()
class PROJECTCORERUNTIME_API ULevelsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void LoadLevelAsync(TSoftObjectPtr<UWorld> Level, FStreamableDelegate Callback = FStreamableDelegate());
	ULevelsConfig* GetLevelsConfig();

private:
	UPROPERTY()
	TWeakObjectPtr<ULevelsConfig> LevelsConfig;
	UPROPERTY()
	TWeakObjectPtr<UAssetsSubsystem> AssetsService;
}; 
