// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ActorsFactory.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectCoreRuntime/Components/Base/ComponentsContainer.h"
#include "ProjectCoreRuntime/Subsystems/ConfigsSubsystem.h"

void UActorsFactory::InitializeCharacter(ABaseCharacter* InCharacter)
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
	auto NewComponentsContainer = NewObject<UComponentsContainer>(GetWorld());
	NewComponentsContainer->Construct();
	NewComponentsContainer->Initialize();
	
	InActor->SetComponentsContainer(NewComponentsContainer);
	InActor->Construct();
	InActor->Initialize();
	
	OnActorActorAdded.ExecuteIfBound(InActor);
}

void UActorsFactory::InitializePawn(ABasePawn* InPawn)
{
	auto NewComponentsContainer = NewObject<UComponentsContainer>(GetWorld());
	NewComponentsContainer->Construct();
	NewComponentsContainer->Initialize();
	
	InPawn->SetComponentsContainer(NewComponentsContainer);
	InPawn->Construct();
	InPawn->Initialize();

	OnPawnAdded.ExecuteIfBound(InPawn);
}

void UActorsFactory::Inject()
{
	ActorsConfig = GetGameInstance()->GetSubsystem<UConfigsSubsystem>()->GetConfig<UActorsConfig>();
}
