// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ActorsFactory.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectCoreRuntime/Components/Base/ComponentsContainer.h"
#include "ProjectCoreRuntime/Subsystems/ConfigsSubsystem.h"

void UActorsFactory::InitializeCharacterActor(ABaseCharacter* InCharacter)
{
	auto NewComponentsContainer = NewObject<UComponentsContainer>(GetWorld());
	NewComponentsContainer->Construct();
	NewComponentsContainer->Initialize();
	
	InCharacter->SetComponentsContainer(NewComponentsContainer);
	InCharacter->Construct();
	if (auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PlayerController->Possess(InCharacter);
	}
	InCharacter->Initialize();
	
	OnCharacterActorAdded.ExecuteIfBound(InCharacter);
}

void UActorsFactory::InitializeActor(ABaseActor* InActor)
{
	InActor->Construct();
	InActor->Initialize();
	
	OnActorActorAdded.ExecuteIfBound(InActor);
}

void UActorsFactory::Inject()
{
	ActorsConfig = GetGameInstance()->GetSubsystem<UConfigsSubsystem>()->GetConfig<UActorsConfig>();
}
