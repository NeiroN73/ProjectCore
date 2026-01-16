// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "BaseFactory.h"

#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentsContainer.h"
#include "ProjectCoreRuntime/Interfaces/Initializable.h"
#include "ProjectCoreRuntime/Interfaces/PreInitializable.h"
#include "ProjectCoreRuntime/Services/TickService.h"
#include "ProjectCoreRuntime/Services/Base/Fragmentable.h"
#include "ProjectCoreRuntime/Services/Base/Tickable.h"

void UBaseFactory::Inject(UInstallerContainer* Container)
{
	InstallerContainer = Container;

	TickService = Container->Resolve<UTickService>();
}

void UBaseFactory::WorldChanged(UWorld* NewWorld)
{
	World = NewWorld;
}

void UBaseFactory::GetAllAccesses(UObject* Object)
{
	GetAccessInjectable(Object);
	GetAccessFragmentable(Object);
	GetAccessPreInitializable(Object);
	GetAccessInitializable(Object);
	GetAccessTickable(Object);
}

void UBaseFactory::GetAccessInjectable(UObject* Object)
{
	if (auto Injectable = Cast<IInjectable>(Object))
	{
		Injectable->Inject(InstallerContainer);
	}
}

void UBaseFactory::GetAccessPreInitializable(UObject* Object)
{
	if (auto PreInitializable = Cast<IPreInitializable>(Object))
	{
		PreInitializable->PreInitialize();
	}
}

void UBaseFactory::GetAccessInitializable(UObject* Object)
{
	if (auto Initializable = Cast<IInitializable>(Object))
	{
		Initializable->Initialize();
	}
}

void UBaseFactory::GetAccessTickable(UObject* Object)
{
	if (auto Tickable = Cast<ITickable>(Object))
	{
		TickService->RegisterTick(Tickable);
	}
}

void UBaseFactory::GetAccessFragmentable(UObject* Object)
{
	if (auto Fragmentable = Cast<IFragmentable>(Object))
	{
		auto FragmentsContainer = NewObject<UFragmentsContainer>();
		FragmentsContainers.Add(FragmentsContainer);
		Fragmentable->BuildFragments(FragmentsContainer);
		auto Fragments = FragmentsContainer->GetFragments();
		for (auto Fragment : Fragments)
		{
			GetAccessInjectable(Fragment);
			GetAccessPreInitializable(Fragment);
			GetAccessInitializable(Fragment);
			GetAccessTickable(Fragment);
		}
	}
}
