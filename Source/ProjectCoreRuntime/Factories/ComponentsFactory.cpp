// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ComponentsFactory.h"

UBaseComponent* UComponentsFactory::Create(UBaseComponent* NewComponent, UComponentsContainer* InComponentsContainer)
{
	NewComponent->Construct();
	NewComponent->InjectComponentsContainer(InComponentsContainer);
	NewComponent->PreInitialize();
	NewComponent->Initialize();
	NewComponent->SetTickEnable(true);
	return NewComponent;
}
