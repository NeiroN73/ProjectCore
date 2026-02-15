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

void UComponentsContainer::Build()
{
	for (auto [Class, Component] : ComponentsByType)
	{
		ComponentsFactory->Create(Component, this);
	}
}

void UComponentsContainer::Construct()
{
	ComponentsFactory = GetWorld()->GetGameInstance()->GetSubsystem<UComponentsFactory>();
}

void UComponentsContainer::Initialize()
{
}
