// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "HandlersFactory.h"

#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Handlers/CharacterHandler.h"
#include "ProjectCoreRuntime/Handlers/Base/ActorHandler.h"
#include "ProjectCoreRuntime/TableConfigs/HandlersTableData.h"

void UHandlersFactory::InitializeCharacterHandler(ACharacterHandler* Handler)
{
	InitializeHandler(Handler);

	//OnCharacterHandlerAdded.Execute(Handler);
}

void UHandlersFactory::InitializeHandler(AActor* Actor)
{
	GetAccessInjectable(Actor);
	GetAccessFragmentable(Actor);
	GetAccessPreInitializable(Actor);
	GetAccessInitializable(Actor);
	GetAccessTickable(Actor);

	if (auto Handler = Cast<AActorHandler>(Actor))
	{
		OnActorHandlerAdded.ExecuteIfBound(Handler);
	}
}

void UHandlersFactory::Inject(UInstallerContainer* Container)
{
	Super::Inject(Container);
	
	HandlersConfig = Container->Resolve<UHandlersConfig>();
}
