// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ConfigsSubsystem.h"

bool UConfigsSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer))
	{
		return true;
	}
	return false;
}
