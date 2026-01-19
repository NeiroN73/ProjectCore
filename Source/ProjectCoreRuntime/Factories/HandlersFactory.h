// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseFactory.h"
#include "ProjectCoreRuntime/Configs/HandlersConfig.h"
#include "ProjectCoreRuntime/Handlers/CharacterHandler.h"
#include "ProjectCoreRuntime/Handlers/Base/ActorHandler.h"
#include "HandlersFactory.generated.h"

class UHandlersConfig;
class AGameplayGameMode;

DECLARE_DELEGATE_OneParam(FOnCharacterHandlerAdded, ACharacterHandler*)
DECLARE_DELEGATE_OneParam(FOnActorHandlerAdded, AActorHandler*)

UCLASS()
class PROJECTCORERUNTIME_API UHandlersFactory : public UBaseFactory
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TWeakObjectPtr<UHandlersConfig> HandlersConfig;
	
public:
	FOnCharacterHandlerAdded OnCharacterHandlerAdded;
	FOnActorHandlerAdded OnActorHandlerAdded;
	
	template<class TActor = AActorHandler>
	TActor* SpawnHandler(FGameplayTag Tag = FGameplayTag::EmptyTag,
		FVector Location = FVector::ZeroVector,
		FRotator Rotation = FRotator::ZeroRotator)
	{
		if (auto Class = HandlersConfig->HandlersById.Find(Tag))
		{
			if (auto Handler = World->SpawnActor<TActor>(*Class, Location, Rotation))
			{
				InitializeHandler(Handler);
				return Handler;
			}
		}
		
		return nullptr;
	}

	template<class TCharacter = ACharacterHandler>
	TCharacter* SpawnCharacterHandler(FGameplayTag Tag = FGameplayTag::EmptyTag,
		FVector Location = FVector::ZeroVector,
		FRotator Rotation = FRotator::ZeroRotator)
	{
		if (auto Class = HandlersConfig->HandlersById.Find(Tag))
		{
			if (auto Handler = World->SpawnActor<TCharacter>(*Class, Location, Rotation))
			{
				InitializeCharacterHandler(Handler);
				return Handler;
			}
		}

		return nullptr;
	}

	void InitializeCharacterHandler(ACharacterHandler* Handler);
	void InitializeHandler(AActorHandler* Actor);

	virtual void Inject(UInstallerContainer* Container) override;
};