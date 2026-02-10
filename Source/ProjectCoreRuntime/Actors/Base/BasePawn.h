// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS(Abstract)
class PROJECTCORERUNTIME_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FGameplayTag Tag;
	
	ABasePawn();
};
