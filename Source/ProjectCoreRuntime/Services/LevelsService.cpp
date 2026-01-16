// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "LevelsService.h"

#include "AssetsService.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectCoreRuntime/Configs/LevelsConfig.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"

void ULevelsService::LoadLevelAsync(TSoftObjectPtr<UWorld> Level, FStreamableDelegate Callback)
{
	AssetsService->LoadAsync("Test", Level.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this, Level, Callback]
	{
		Callback.Execute();
		UGameplayStatics::OpenLevelBySoftObjectPtr(World, Level);
	}));
}

void ULevelsService::Inject(UInstallerContainer* Container)
{
	LevelsConfig = Container->Resolve<ULevelsConfig>();
	AssetsService = Container->Resolve<UAssetsService>();
}

ULevelsConfig* ULevelsService::GetLevelsConfig()
{
	return LevelsConfig.Get();
}
