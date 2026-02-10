#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Componentable.generated.h"

class UComponentsContainer;

UINTERFACE()
class UComponentable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTCORERUNTIME_API IComponentable
{
	GENERATED_BODY()

public:
	virtual void BuildComponents(UComponentsContainer* InComponentsContainer) = 0;
};