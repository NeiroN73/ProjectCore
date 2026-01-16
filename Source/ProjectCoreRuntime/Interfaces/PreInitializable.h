// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PreInitializable.generated.h"

UINTERFACE()
class UPreInitializable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTCORERUNTIME_API IPreInitializable
{
	GENERATED_BODY()

public:
	virtual void PreInitialize() = 0;
};
