// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "BasePawn.h"

#include "ProjectCoreRuntime/Components/Base/ComponentsContainer.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

FGameplayTag ABasePawn::GetTag()
{
	return Tag;
}

UComponentsContainer* ABasePawn::GetComponentsContainer()
{
	return ComponentsContainer;
}

void ABasePawn::SetComponentsContainer(UComponentsContainer* InComponentsContainer)
{
	ComponentsContainer = InComponentsContainer;

	auto Components = GetComponents();
	for (UActorComponent* Component : Components)
	{
		GetComponentsContainer()->TryAddComponent(Component);
	}
}
