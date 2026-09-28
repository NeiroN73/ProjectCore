// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "LevelsConfig.h"

TSoftObjectPtr<UWorld> ULevelsConfig::GetLevel(FGameplayTag InName)
{
	return LevelsByName.FindRef(InName);
}
