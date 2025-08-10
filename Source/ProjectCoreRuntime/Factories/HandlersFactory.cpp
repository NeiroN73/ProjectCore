// Copyright Floruit, Inc. All Rights Reserved.


#include "HandlersFactory.h"

#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Handlers/CharacterHandler.h"
#include "ProjectCoreRuntime/Handlers/Base/ActorHandler.h"
#include "ProjectCoreRuntime/TableConfigs/HandlersTableData.h"

void UHandlersFactory::InitializeCharacterHandler(ACharacterHandler* Handler)
{
	auto Data = HandlersTableConfig->FindRow<FHandlersTableData>(Handler->Id, "");
	Handler->Data = Data;
	InitializeHandler(Handler);

	OnCharacterHandlerAdded.ExecuteIfBound(Handler);
}

void UHandlersFactory::InitializeHandler(AActor* Actor)
{
	CastInterfaces(Actor);

	if (auto Handler = Cast<AActorHandler>(Actor))
	{
		OnActorHandlerAdded.ExecuteIfBound(Handler);
	}
}

void UHandlersFactory::Inject(UInstallerContainer* Container)
{
	Super::Inject(Container);
	
	HandlersTableConfig = Container->ResolveTableConfig<FHandlersTableData>();
}
