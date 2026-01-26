#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Fragmentable.generated.h"

class UFragmentsContainer;

UINTERFACE()
class UFragmentable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTCORERUNTIME_API IFragmentable
{
	GENERATED_BODY()

public:
	virtual void BuildFragments(UFragmentsContainer* FragmentsContainer) = 0;
	virtual UFragmentsContainer* GetFragmentsContainer() = 0;
};