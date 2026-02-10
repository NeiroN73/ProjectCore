// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ActorsFactory.h"

#include "Kismet/GameplayStatics.h"

void UActorsFactory::InitializeCharacterActor(ABaseCharacter* InActor)
{
	if (auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PlayerController->Possess(InActor);
	}

	OnCharacterActorAdded.ExecuteIfBound(InActor);
}

void UActorsFactory::InitializeActor(ABaseActor* InActor)
{
	OnActorActorAdded.ExecuteIfBound(InActor);
}
