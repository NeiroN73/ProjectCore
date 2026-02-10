// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "LevelsSubsystem.h"

#include "AssetsSubsystem.h"
#include "Kismet/GameplayStatics.h"

void ULevelsSubsystem::LoadLevelAsync(TSoftObjectPtr<UWorld> Level, FStreamableDelegate Callback)
{
	AssetsService->LoadAsync("Test", Level.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this, Level, Callback]
	{
		if (Callback.IsBound())
		{
			Callback.Execute();
		}
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), Level);
	}));
}

ULevelsConfig* ULevelsSubsystem::GetLevelsConfig()
{
	return LevelsConfig.Get();
}
