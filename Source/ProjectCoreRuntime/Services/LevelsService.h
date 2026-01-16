// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Service.h"
#include "Engine/StreamableManager.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "LevelsService.generated.h"

class UAssetsService;
class ULevelsConfig;

UCLASS()
class PROJECTCORERUNTIME_API ULevelsService : public UService,
public IInjectable
{
	GENERATED_BODY()

public:
	void LoadLevelAsync(TSoftObjectPtr<UWorld> Level, FStreamableDelegate Callback);
	virtual void Inject(UInstallerContainer* Container) override;
	ULevelsConfig* GetLevelsConfig();

private:
	UPROPERTY()
	TWeakObjectPtr<ULevelsConfig> LevelsConfig;
	UPROPERTY()
	TWeakObjectPtr<UAssetsService> AssetsService;
}; 
