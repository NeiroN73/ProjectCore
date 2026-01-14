// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ScreensService.h"
#include "Base/Service.h"
#include "ProjectCoreRuntime/Configs/LevelsConfig.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "LevelsService.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API ULevelsService : public UService,
public IInjectable
{
	GENERATED_BODY()

public:
	void LoadLevelAsync(TSoftObjectPtr<UWorld> Level, FStreamableDelegate Callback);
	virtual void Inject(UInstallerContainer* Container) override;
	TObjectPtr<ULevelsConfig> GetLevelsConfig();

private:
	UPROPERTY()
	TWeakObjectPtr<UScreensService> ViewsService;
	UPROPERTY()
	TWeakObjectPtr<ULevelsConfig> LevelsConfig;
	UPROPERTY()
	TWeakObjectPtr<UAssetsService> AssetsService;
}; 
