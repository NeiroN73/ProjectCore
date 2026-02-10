// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetsSubsystem.h"
#include "PreloadSubsystem.generated.h"

class UScreensSubsystem;
class UConfig;
class IPreloadConfig;
class UAssetsSubsystem;
class IPreloadable;
class UHistorySaveState;

DECLARE_DELEGATE(FOnPreloadCompleted)

UCLASS()
class PROJECTCORERUNTIME_API UPreloadSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Inject();

	void StartPreload(TSet<FName> InPreloadIds, FOnPreloadCompleted Callback);
	void CompletePreload(const FOnPreloadCompleted& Callback);
	void ReleasePreloadAssets();

private:
	UPROPERTY()
	TWeakObjectPtr<UAssetsSubsystem> AssetsService;
	UPROPERTY()
	TWeakObjectPtr<UScreensSubsystem> ScreensService;
	
	TArray<IPreloadConfig*> PreloadConfigs;
	
	UPROPERTY()
	TSet<FName> HistoryPreloadIds;
	UPROPERTY()
	TMap<FName, FSoftObjectPath> CurrentPathsById;
};
