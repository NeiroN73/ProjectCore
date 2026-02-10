// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseFactory.h"
#include "ProjectCoreRuntime/Actors/Base/BaseActor.h"
#include "ProjectCoreRuntime/Actors/Base/BaseCharacter.h"
#include "ProjectCoreRuntime/Configs/ActorsConfig.h"
#include "ActorsFactory.generated.h"

class UActorsConfig;
class AGameplayGameMode;

DECLARE_DELEGATE_OneParam(FOnCharacterActorAdded, ABaseCharacter*)
DECLARE_DELEGATE_OneParam(FOnActorActorAdded, ABaseActor*)

UCLASS()
class PROJECTCORERUNTIME_API UActorsFactory : public UBaseFactory
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TWeakObjectPtr<UActorsConfig> ActorsConfig;
	
public:
	FOnCharacterActorAdded OnCharacterActorAdded;
	FOnActorActorAdded OnActorActorAdded;
	
	template<class TActor = ABaseActor>
	TActor* SpawnActor(FGameplayTag Tag = FGameplayTag::EmptyTag,
		FVector Location = FVector::ZeroVector,
		FRotator Rotation = FRotator::ZeroRotator)
	{
		if (auto Class = ActorsConfig->ActorsById.Find(Tag))
		{
			if (auto Actor = GetWorld()->SpawnActor<TActor>(*Class, Location, Rotation))
			{
				InitializeActor(Actor);
				return Actor;
			}
		}
		
		return nullptr;
	}

	template<class TCharacter = ABaseCharacter>
	TCharacter* SpawnCharacterActor(FGameplayTag Tag = FGameplayTag::EmptyTag,
		FVector Location = FVector::ZeroVector,
		FRotator Rotation = FRotator::ZeroRotator)
	{
		if (auto Class = ActorsConfig->ActorsById.Find(Tag))
		{
			if (auto Actor = GetWorld()->SpawnActor<TCharacter>(*Class, Location, Rotation))
			{
				InitializeCharacterActor(Actor);
				return Actor;
			}
		}

		return nullptr;
	}

	void InitializeCharacterActor(ABaseCharacter* InActor);
	void InitializeActor(ABaseActor* InActor);
};