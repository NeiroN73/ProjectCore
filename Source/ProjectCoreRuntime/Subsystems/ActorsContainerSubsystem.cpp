// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ActorsContainerSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectCoreRuntime/Factories/ActorsFactory.h"


void UActorsContainerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	CharactersById.Empty();
	ActorsById.Empty();
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		if (auto CharacterActor = Cast<ABaseCharacter>(Actor))
		{
			ActorsFactory->InitializeCharacterActor(CharacterActor);
		}
		else if (auto ActorActor = Cast<ABaseActor>(Actor))
		{
			ActorsFactory->InitializeActor(ActorActor);
		}
	}
}

void UActorsContainerSubsystem::AddCharacterActor(ABaseCharacter* CharacterActor)
{
	CharactersById.Add(CharacterActor->GetTag(), CharacterActor);
}

void UActorsContainerSubsystem::AddActorActor(ABaseActor* Actor)
{
	ActorsById.Add(Actor->GetTag(), Actor);
}
