// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "LevelsConfig.h"

TSoftObjectPtr<UWorld> ULevelsConfig::GetLevel(ELevelNames InName)
{
	return LevelsByName.FindRef(InName);
}
