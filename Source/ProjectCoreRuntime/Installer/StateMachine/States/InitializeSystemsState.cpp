// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "InitializeSystemsState.h"

#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Services/TickService.h"
#include "ProjectCoreRuntime/SaveStates/HistorySaveState.h"

void UInitializeSystemsState::Enter()
{
	InitializeSystems();
	
	StateMachine->NextState();
}

void UInitializeSystemsState::InitializeSystems()
{
	auto Container = StateMachine->InstallerContainer;
	
	auto Injectables = Container->ResolveAllImplements<IInjectable>();
	for (auto Injectable : Injectables)
	{
		Injectable->Inject(Container);
	}

	auto Fragmentables = Container->ResolveAllImplements<IFragmentable>();
	for (auto Fragmentable : Fragmentables)
	{
		Fragmentable->BuildFragments();
	}

	auto Initializables = Container->ResolveAllImplements<IInitializable>();
	for (auto Initializable : Initializables)
	{
		Initializable->Initialize();
	}

	auto Tickables = Container->ResolveAllImplements<ITickable>();
	auto TickService = Container->Resolve<UTickService>();
	for (auto Tickable : Tickables)
	{
		TickService->RegisterTick(Tickable);
	}
}