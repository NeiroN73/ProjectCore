// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "BaseCharacter.h"


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
}
