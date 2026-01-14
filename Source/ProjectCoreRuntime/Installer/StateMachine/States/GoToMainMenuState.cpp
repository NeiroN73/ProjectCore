// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "GoToMainMenuState.h"

#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Services/LevelsService.h"

void UGoToMainMenuState::Enter()
{
	LevelsService = StateMachine->InstallerContainer->Resolve<ULevelsService>();
	LevelsService->LoadLevelAsync(LevelsService->GetLevelsConfig()->MainMenuLevel,
		FStreamableDelegate::CreateLambda([this]
	{
		StateMachine->NextState();
	}));
}
