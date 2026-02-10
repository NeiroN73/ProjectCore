// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Configs.generated.h"

class UConfig;

UCLASS()
class PROJECTCORERUNTIME_API UConfigs : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<UConfig>, TObjectPtr<UConfig>> Configs;
};