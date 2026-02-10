// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Base/Config.h"
#include "ActorsConfig.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UActorsConfig : public UConfig
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, TSubclassOf<AActor>> ActorsById;
};
