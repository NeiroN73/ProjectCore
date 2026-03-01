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
