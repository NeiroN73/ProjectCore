// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ActorsSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectCoreRuntime/Factories/ActorsFactory.h"


void UActorsSubsystem::AddCharacterActor(ABaseCharacter* CharacterActor)
{
	CharactersById.Add(CharacterActor->GetTag(), CharacterActor);
}

void UActorsSubsystem::AddActorActor(ABaseActor* Actor)
{
	ActorsById.Add(Actor->GetTag(), Actor);
}

void UActorsSubsystem::Inject()
{
	ActorsFactory = GetWorld()->GetGameInstance()->GetSubsystem<UActorsFactory>();
}

void UActorsSubsystem::Initialize()
{
	CharactersById.Empty();
	ActorsById.Empty();
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		if (auto CharacterActor = Cast<ABaseCharacter>(Actor))
		{
			ActorsFactory->InitializeCharacter(CharacterActor);
		}
		else if (auto ActorActor = Cast<ABaseActor>(Actor))
		{
			ActorsFactory->InitializeActor(ActorActor);
		}
	}
}
