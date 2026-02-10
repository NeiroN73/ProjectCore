// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseComponent.generated.h"

class UComponentsContainer;

UCLASS(Abstract)
class PROJECTCORERUNTIME_API UBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void SetComponentsContainer(UComponentsContainer* InComponentsContainer) {}
};
