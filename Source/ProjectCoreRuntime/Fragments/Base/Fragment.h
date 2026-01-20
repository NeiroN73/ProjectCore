// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Fragment.generated.h"

class UFragmentsContainer;

UCLASS(Abstract)
class PROJECTCORERUNTIME_API UFragment : public UObject
{
	GENERATED_BODY()

public:
	virtual void InitializeFragments(UFragmentsContainer* InFragmentsContainer) {}
};
