// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "CharacterFragment.h"

void UCharacterFragment::Initialize(ACharacterHandler* InCharacterHandler, AController* InController)
{
	Character = MakeWeakObjectPtr<ACharacterHandler>(InCharacterHandler);
	Controller = MakeWeakObjectPtr<AController>(InController);
}
