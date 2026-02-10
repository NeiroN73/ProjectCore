// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "PreloadSubsystem.h"

#include "AssetsSubsystem.h"
#include "ScreensSubsystem.h"
#include "ProjectCoreRuntime/Configs/Base/PreloadConfig.h"
#include "ProjectCoreRuntime/UI/Loading/LoadingScreen.h"

void UPreloadSubsystem::Inject()
{
	//PreloadConfigs = Get->ResolveAllImplements<IPreloadConfig>();
	
	AssetsService = GetGameInstance()->GetSubsystem<UAssetsSubsystem>();
	ScreensService = GetGameInstance()->GetSubsystem<UScreensSubsystem>();
}

void UPreloadSubsystem::StartPreload(TSet<FName> InPreloadIds, FOnPreloadCompleted Callback)
{
	ScreensService->Open<ULoadingScreen>();
	
	CurrentPathsById.Empty();

	HistoryPreloadIds = InPreloadIds;
	
	for (auto Config : PreloadConfigs)
	{
		TMap<FName, FSoftObjectPath> ConfigPaths = Config->GetSoftPaths();
		
		for (const auto& [Id, Path] : ConfigPaths)
		{
			if (HistoryPreloadIds.Contains(Id))
			{
				CurrentPathsById.Add(Id, Path);
			}
		}
	}

	int32 PathsCount = CurrentPathsById.Num();
	if (PathsCount == 0)
	{
		CompletePreload(Callback);
		return;
	}

	for (const auto& Path : CurrentPathsById)
	{
		AssetsService->LoadAsync(Path.Key, Path.Value,
			FStreamableDelegate::CreateLambda([this, &PathsCount, Callback]
			{
				if ((PathsCount--) == 0)
				{
					CompletePreload(Callback);
				}
			}));
	}
}

void UPreloadSubsystem::CompletePreload(const FOnPreloadCompleted& Callback)
{
	ScreensService->Close();
	
	Callback.Execute();
}

void UPreloadSubsystem::ReleasePreloadAssets()
{
	for (auto Id : HistoryPreloadIds)
	{
		if (auto Asset = AssetsService->HandlesById.FindRef(Id))
		{
			if (Asset)
			{
				Asset->ReleaseHandle();
			}
			AssetsService->HandlesById.Remove(Id);
		}
	}
}
