// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LevelNames.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API ULevelNames : public UObject
{
	GENERATED_BODY()

public:
	static const FName EntryPoint;
	static const FName Gameplay;
};
