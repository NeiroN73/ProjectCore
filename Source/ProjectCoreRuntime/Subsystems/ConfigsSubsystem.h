// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Configs/Base/Config.h"
#include "ProjectCoreRuntime/Configs/Base/Configs.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ConfigsSubsystem.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UConfigsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfigs> Configs;
	
public:
	template<class TConfig = UConfig>
	TConfig* GetConfig()
	{
		if (auto Config = Configs->Configs.FindRef(TConfig::StaticClass()))
		{
			return Cast<TConfig>(Config);
		}
		return nullptr;
	}
};
