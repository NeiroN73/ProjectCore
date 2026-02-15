// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Injectable.generated.h"

UINTERFACE()
class UInjectable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTCORERUNTIME_API IInjectable
{
	GENERATED_BODY()
public:
	virtual void Inject() = 0;
};
