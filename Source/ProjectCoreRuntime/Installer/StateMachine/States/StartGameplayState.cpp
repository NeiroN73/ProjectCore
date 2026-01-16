// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "StartGameplayState.h"

#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Services/LevelsService.h"

void UStartGameplayState::Enter()
{
	// LevelsService = StateMachine->InstallerContainer->Resolve<ULevelsService>();
	// LevelsService->LoadLevelAsync(LevelsService->GetLevelsConfig()->GetLevel(ELevelNames::Gameplay),
	// 	FStreamableDelegate::CreateLambda([this]
	// {
	// 	StateMachine->NextState();
	// }));
}
