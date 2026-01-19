// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "CharacterHandler.h"


ACharacterHandler::ACharacterHandler()
{
	PrimaryActorTick.bCanEverTick = false;
}

FGameplayTag ACharacterHandler::GetTag()
{
	return Tag;
}
