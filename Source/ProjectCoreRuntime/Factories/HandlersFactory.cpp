// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "HandlersFactory.h"

#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Handlers/CharacterHandler.h"
#include "ProjectCoreRuntime/Handlers/Base/ActorHandler.h"

void UHandlersFactory::InitializeCharacterHandler(ACharacterHandler* Handler)
{
	ExecuteInjectable(Handler);

	if (auto PlayerController = UGameplayStatics::GetPlayerController(World, 0))
	{
		PlayerController->Possess(Handler);
	}
	
	ExecuteFragmentable(Handler);
	ExecutePreInitializable(Handler);
	ExecuteInitializable(Handler);
	ExecuteTickable(Handler);

	//OnCharacterHandlerAdded.Execute(Handler);
}

void UHandlersFactory::InitializeHandler(AActorHandler* InHandler)
{
	ExecuteInjectable(InHandler);
	ExecuteFragmentable(InHandler);
	ExecutePreInitializable(InHandler);
	ExecuteInitializable(InHandler);
	ExecuteTickable(InHandler);

	OnActorHandlerAdded.ExecuteIfBound(InHandler);
}

void UHandlersFactory::Inject(UInstallerContainer* Container)
{
	Super::Inject(Container);
	
	HandlersConfig = Container->Resolve<UHandlersConfig>();
}
