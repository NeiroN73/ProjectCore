// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "AssetsSubsystem.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UAssetsSubsystem::LoadAsync(FName Id, const FSoftObjectPath& TargetToStream,
	FStreamableDelegate Delegate)
{
	if (UAssetManager::IsInitialized())
	{
		auto Handle = UAssetManager::GetStreamableManager().RequestAsyncLoad(TargetToStream, Delegate);
		HandlesById.Add(Id, Handle);
	}
}

TSharedPtr<FStreamableHandle> UAssetsSubsystem::LoadPrimaryAsync(const FPrimaryAssetId& AssetToLoad,
	FStreamableDelegate Delegate)
{
	if (auto AssetManager = UAssetManager::GetIfInitialized())
	{
		return AssetManager->LoadPrimaryAsset(AssetToLoad, TArray<FName>(), Delegate);
	}
	
	return TSharedPtr<FStreamableHandle>();
}
