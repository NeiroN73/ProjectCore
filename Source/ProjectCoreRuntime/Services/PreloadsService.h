// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetsService.h"
#include "Base/Service.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "PreloadsService.generated.h"

class UScreensService;
class UConfig;
class IPreloadConfig;
class UAssetsService;
class IPreloadable;
class UHistorySaveState;

DECLARE_DELEGATE(FOnPreloadCompleted)

UCLASS()
class PROJECTCORERUNTIME_API UPreloadsService : public UService,
public IInjectable
{
	GENERATED_BODY()

public:
	virtual void Inject(UInstallerContainer* Container) override;

	void StartPreload(TSet<FName> InPreloadIds, FOnPreloadCompleted Callback);
	void CompletePreload(const FOnPreloadCompleted& Callback);
	void ReleasePreloadAssets();

private:
	UPROPERTY()
	TWeakObjectPtr<UAssetsService> AssetsService;
	UPROPERTY()
	TWeakObjectPtr<UScreensService> ScreensService;
	
	TArray<IPreloadConfig*> PreloadConfigs;
	
	UPROPERTY()
	TSet<FName> HistoryPreloadIds;
	UPROPERTY()
	TMap<FName, FSoftObjectPath> CurrentPathsById;
};
