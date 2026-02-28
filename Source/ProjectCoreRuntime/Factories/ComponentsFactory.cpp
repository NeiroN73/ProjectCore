// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ComponentsFactory.h"

UActorComponent* UComponentsFactory::Create(UActorComponent* NewComponent, UComponentsContainer* InComponentsContainer)
{
	if (auto BaseComponent = Cast<UBaseComponent>(NewComponent))
	{
		BaseComponent->Construct();
		BaseComponent->InjectComponentsContainer(InComponentsContainer);
		BaseComponent->PreInitialize();
		BaseComponent->Initialize();
		BaseComponent->SetTickEnable(true);
	}
	return NewComponent;
}
