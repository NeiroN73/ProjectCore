#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Fragmentable.generated.h"

class UFragment;

UINTERFACE()
class UFragmentable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTCORERUNTIME_API IFragmentable
{
	GENERATED_BODY()

public:
	virtual void BuildFragments() = 0;
};