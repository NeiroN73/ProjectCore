// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Actors/Base/BaseActor.h"
#include "ProjectCoreRuntime/Factories/ActorsFactory.h"
#include "ActorsContainerSubsystem.generated.h"

class ABaseCharacter;

UCLASS()
class PROJECTCORERUNTIME_API UActorsContainerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UPROPERTY()
	TMap<FGameplayTag, ABaseCharacter*> CharactersById;
	UPROPERTY()
	TMap<FGameplayTag, ABaseActor*> ActorsById;

	template<typename TCharacterActor = ABaseCharacter>
	TCharacterActor* GetCharacterActor(FGameplayTag Tag)
	{
		if (auto Character = CharactersById.FindRef(Tag))
		{
			return Cast<TCharacterActor>(Character);
		}

		return nullptr;
	}
	
	template<typename TActor = ABaseActor>
	TActor* GetActorActor(FGameplayTag Tag)
	{
		if (auto Actor = ActorsById.FindRef(Tag))
		{
			return Cast<TActor>(Actor);
		}

		return nullptr;
	}

private:
	void AddCharacterActor(ABaseCharacter* CharacterActor);
	void AddActorActor(ABaseActor* Actor);

	UPROPERTY()
	TWeakObjectPtr<UActorsFactory> ActorsFactory;
};
