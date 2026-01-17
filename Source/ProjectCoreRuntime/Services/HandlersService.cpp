// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "HandlersService.h"

#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Handlers/CharacterHandler.h"
#include "ProjectCoreRuntime/Handlers/Base/ActorHandler.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"

void UHandlersService::Inject(UInstallerContainer* Container)
{
	HandlerFactory = Container->Resolve<UHandlersFactory>();
	HandlerFactory->OnCharacterHandlerAdded.BindLambda([this](ACharacterHandler* CharacterHandler)
	{
		AddCharacterHandler(CharacterHandler);
	});
	HandlerFactory->OnActorHandlerAdded.BindLambda([this](AActorHandler* CharacterHandler)
	{
		AddActorHandler(CharacterHandler);
	});
}

void UHandlersService::WorldChanged(UWorld* NewWorld)
{
	Super::WorldChanged(NewWorld);

	CharactersById.Empty();
	HandlersById.Empty();
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		if (auto CharacterHandler = Cast<ACharacterHandler>(Actor))
		{
			HandlerFactory->InitializeCharacterHandler(CharacterHandler);
		}
		else if (auto ActorHandler = Cast<AActorHandler>(Actor))
		{
			HandlerFactory->InitializeHandler(ActorHandler);
		}
	}
}

void UHandlersService::AddCharacterHandler(ACharacterHandler* CharacterHandler)
{
	CharactersById.Add(CharacterHandler->Id, CharacterHandler);
}

void UHandlersService::AddActorHandler(AActorHandler* Handler)
{
	HandlersById.Add(Handler->Id, Handler);
}
