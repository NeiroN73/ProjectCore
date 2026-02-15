// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "BasePawn.h"

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
}
