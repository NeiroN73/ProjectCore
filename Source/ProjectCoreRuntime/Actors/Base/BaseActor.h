// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

UCLASS(Abstract)
class PROJECTCORERUNTIME_API ABaseActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag Tag;

public:
	FGameplayTag GetTag();
};
