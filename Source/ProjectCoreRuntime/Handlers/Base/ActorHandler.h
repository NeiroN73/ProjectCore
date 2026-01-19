// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Handlerable.h"
#include "GameFramework/Actor.h"
#include "ActorHandler.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API AActorHandler : public AActor,
public IHandlerable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag Tag;

public:
	FGameplayTag GetTag();
};
