// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Service.h"
#include "ProjectCoreRuntime/Handlers/Base/ActorHandler.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "HandlersService.generated.h"

class ACharacterHandler;
class UHandlersFactory;

UCLASS()
class PROJECTCORERUNTIME_API UHandlersService : public UService,
public IInjectable
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TMap<FGameplayTag, ACharacterHandler*> CharactersById;
	UPROPERTY()
	TMap<FGameplayTag, AActorHandler*> HandlersById;
	
	virtual void Inject(UInstallerContainer* Container) override;
	virtual void WorldChanged(UWorld* NewWorld) override;

	template<typename TCharacterHandler = ACharacterHandler>
	TCharacterHandler* GetCharacterHandler(FGameplayTag Tag)
	{
		if (auto Character = CharactersById.FindRef(Tag))
		{
			return Cast<TCharacterHandler>(Character);
		}

		return nullptr;
	}
	
	template<typename THandler = AActorHandler>
	THandler* GetActorHandler(FGameplayTag Tag)
	{
		if (auto Actor = HandlersById.FindRef(Tag))
		{
			return Cast<THandler>(Actor);
		}

		return nullptr;
	}

private:
	void AddCharacterHandler(ACharacterHandler* CharacterHandler);
	void AddActorHandler(AActorHandler* Handler);

	UPROPERTY()
	TWeakObjectPtr<UHandlersFactory> HandlerFactory;
};
