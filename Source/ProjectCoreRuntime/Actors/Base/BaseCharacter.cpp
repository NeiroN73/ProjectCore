// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "BaseCharacter.h"

#include "ProjectCoreRuntime/Components/Base/ComponentsContainer.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

FGameplayTag ABaseCharacter::GetTag()
{
	return Tag;
}

UComponentsContainer* ABaseCharacter::GetComponentsContainer()
{
	return ComponentsContainer;
}

void ABaseCharacter::SetComponentsContainer(UComponentsContainer* InComponentsContainer)
{
	ComponentsContainer = InComponentsContainer;

	GatherDefaultComponentsInContainer();
}

void ABaseCharacter::GatherDefaultComponentsInContainer()
{
	auto Components = GetComponents();
	for (UActorComponent* Component : Components)
	{
		GetComponentsContainer()->TryAddComponent(Component);
	}
}
