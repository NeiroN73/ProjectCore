// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseFactory.h"
#include "ProjectCoreRuntime/Actors/Base/BaseActor.h"
#include "ProjectCoreRuntime/Actors/Base/BaseCharacter.h"
#include "ProjectCoreRuntime/Actors/Base/BasePawn.h"
#include "ProjectCoreRuntime/Configs/ActorsConfig.h"
#include "ProjectCoreRuntime/Interfaces/Injectable.h"
#include "ActorsFactory.generated.h"

class UActorsConfig;
class AGameplayGameMode;

DECLARE_DELEGATE_OneParam(FOnCharacterAdded, ABaseCharacter*)
DECLARE_DELEGATE_OneParam(FOnActorAdded, ABaseActor*)
DECLARE_DELEGATE_OneParam(FOnPawnAdded, ABasePawn*)

UCLASS()
class PROJECTCORERUNTIME_API UActorsFactory : public UBaseFactory,
public IInjectable
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TWeakObjectPtr<UActorsConfig> ActorsConfig;
	
public:
	FOnCharacterAdded OnCharacterActorAdded;
	FOnActorAdded OnActorActorAdded;
	FOnPawnAdded OnPawnAdded;
	
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

	template<class TActor = ABasePawn>
	TActor* SpawnPawn(FGameplayTag Tag = FGameplayTag::EmptyTag,
	FVector Location = FVector::ZeroVector,
	FRotator Rotation = FRotator::ZeroRotator)
	{
		if (auto Class = ActorsConfig->ActorsById.Find(Tag))
		{
			if (auto Actor = GetWorld()->SpawnActor<TActor>(*Class, Location, Rotation))
			{
				InitializePawn(Actor);
				return Actor;
			}
		}
		
		return nullptr;
	}

	template<class TCharacter = ABaseCharacter>
	TCharacter* SpawnCharacter(FGameplayTag Tag = FGameplayTag::EmptyTag,
		FVector Location = FVector::ZeroVector,
		FRotator Rotation = FRotator::ZeroRotator)
	{
		if (auto Class = ActorsConfig->ActorsById.Find(Tag))
		{
			if (auto Actor = GetWorld()->SpawnActor<TCharacter>(*Class, Location, Rotation))
			{
				InitializeCharacter(Actor);
				return Actor;
			}
		}

		return nullptr;
	}

	virtual void Inject() override;
	
	void InitializeActor(ABaseActor* InActor);
	void InitializePawn(ABasePawn* InPawn);
	void InitializeCharacter(ABaseCharacter* InCharacter);
};