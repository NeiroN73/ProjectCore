// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "UObject/Object.h"
#include "AssetsSubsystem.generated.h"

struct FStreamableHandle;

UCLASS()
class PROJECTCORERUNTIME_API UAssetsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void LoadAsync(FName Id, const FSoftObjectPath& TargetToStream, FStreamableDelegate Delegate);
	TSharedPtr<FStreamableHandle> LoadPrimaryAsync(const FPrimaryAssetId& AssetToLoad, FStreamableDelegate Delegate);

	TMap<FName, TSharedPtr<FStreamableHandle>> HandlesById;
	
	template<typename TObject = UObject>
	TObject* GetLoadedAsset(FName Id)
	{
		if (auto Asset = HandlesById.FindRef(Id))
		{
			if (Asset && Asset->HasLoadCompleted())
			{
				return Cast<TObject>(Asset->GetLoadedAsset());
			}
		}
		return nullptr;
	}
};
