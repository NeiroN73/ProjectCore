// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "BaseCharacter.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

FGameplayTag ABaseCharacter::GetTag()
{
	return Tag;
}
