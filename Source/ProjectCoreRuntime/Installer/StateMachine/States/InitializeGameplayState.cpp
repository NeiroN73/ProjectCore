// Copyright Floruit, Inc. All Rights Reserved.


#include "InitializeGameplayState.h"

#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"

class UMyTestView;

void UInitializeGameplayState::Enter()
{
	auto HandlersFactory = StateMachine->InstallerContainer->Resolve<UHandlersFactory>();
	HandlersFactory->SpawnCharacterHandler("player");
	
	StateMachine->NextState();
}
