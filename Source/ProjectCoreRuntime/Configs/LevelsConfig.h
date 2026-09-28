// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Config.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "LevelsConfig.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API ULevelsConfig : public UConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, TSoftObjectPtr<UWorld>> LevelsByName;

	TSoftObjectPtr<UWorld> GetLevel(FGameplayTag InName);
};
