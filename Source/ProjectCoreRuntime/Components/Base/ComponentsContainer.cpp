// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ComponentsContainer.h"

TArray<UBaseComponent*> UComponentsContainer::GetComponents()
{
	TArray<UBaseComponent*> Result;
	for (auto& [Class, Component] : ComponentsByType)
	{
		Result.Add(Component);
	}
	return Result;
}
