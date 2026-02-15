// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "BaseActor.h"

FGameplayTag ABaseActor::GetTag()
{
	return Tag;
}

UComponentsContainer* ABaseActor::GetComponentsContainer()
{
	return ComponentsContainer;
}

void ABaseActor::SetComponentsContainer(UComponentsContainer* InComponentsContainer)
{
	ComponentsContainer = InComponentsContainer;
}
