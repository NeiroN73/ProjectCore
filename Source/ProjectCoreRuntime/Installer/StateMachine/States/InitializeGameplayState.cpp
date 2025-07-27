// Copyright Floruit, Inc. All Rights Reserved.


#include "InitializeGameplayState.h"

#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Services/HistoryService.h"

class UMyTestView;

void UInitializeGameplayState::Enter()
{
	StateMachine->NextState();
}
