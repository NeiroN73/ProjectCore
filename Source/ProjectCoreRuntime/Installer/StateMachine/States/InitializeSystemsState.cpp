// Copyright Floruit, Inc. All Rights Reserved.


#include "InitializeSystemsState.h"

#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerScope.h"
#include "ProjectCoreRuntime/DependencyInjection/ProjectCoreInstallerScope.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Factories/FragmentsFactory.h"
#include "ProjectCoreRuntime/Services/TickService.h"
#include "ProjectCoreRuntime/SaveStates/HistorySaveState.h"

void UInitializeSystemsState::Enter()
{
	auto Scope = NewObject<UProjectCoreInstallerScope>();
	StateMachine->InstallerContainer = NewObject<UInstallerContainer>();
	StateMachine->InstallerContainer->Register(StateMachine);
	Scope->Configure(StateMachine->InstallerContainer);
	StateMachine->InstallerScopes.Add(Scope);
	
	InitializeSystems();
	
	StateMachine->NextState();
}

void UInitializeSystemsState::InitializeSystems()
{
	auto Container = StateMachine->InstallerContainer;
	
	Injectables = Container->ResolveAllImplements<IInjectable>();
	for (auto Injectable : Injectables)
	{
		Injectable->Inject(Container);
	}

	Fragmentables = Container->ResolveAllImplements<IFragmentable>();
	auto FragmentsFactory = Container->Resolve<UFragmentsFactory>();
	for (auto Fragmentable : Fragmentables)
	{
		Fragmentable->BuildFragments(FragmentsFactory);
	}

	Initializables = Container->ResolveAllImplements<IInitializable>();
	for (auto Initializable : Initializables)
	{
		Initializable->Initialize();
	}

	Tickables = Container->ResolveAllImplements<ITickable>();
	auto TickService = Container->Resolve<UTickService>();
	for (auto Tickable : Tickables)
	{
		TickService->RegisterTick(Tickable);
	}
}