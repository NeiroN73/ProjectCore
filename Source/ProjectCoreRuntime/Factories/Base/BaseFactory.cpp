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
    FragmentsFactory = Container->Resolve<UFragmentsFactory>();
}

void UBaseFactory::WorldChanged(UWorld* NewWorld)
{
	World = NewWorld;
}

void UBaseFactory::ExecuteInjectable(UObject* Object)
{
    if (auto Injectable = Cast<IInjectable>(Object))
    {
        Injectable->Inject(InstallerContainer);
    }
}

void UBaseFactory::ExecuteInitializable(UObject* Object)
{
    if (auto PreInitializable = Cast<IPreInitializable>(Object))
    {
        PreInitializable->PreInitialize();
    }
    if (auto Initializable = Cast<IInitializable>(Object))
    {
        Initializable->Initialize();
    }
}

void UBaseFactory::ExecuteTickable(UObject* Object)
{
    if (auto Tickable = Cast<ITickable>(Object))
    {
        TickService->RegisterTick(Tickable);
    }
}

void UBaseFactory::ExecuteFragmentable(UObject* Object)
{
    if (auto Fragmentable = Cast<IFragmentable>(Object))
    {
        auto FragmentsContainer = NewObject<UFragmentsContainer>();
        FragmentsContainers.Add(FragmentsContainer);
        Fragmentable->BuildFragments(FragmentsContainer);
        auto Fragments = FragmentsContainer->GetFragments();
        
        TArray<UObject*> ObjectFragments;
        ObjectFragments.Reserve(Fragments.Num());
        
        for (auto Fragment : Fragments)
        {
            Fragment->InitializeFragments(FragmentsContainer);
            
            ObjectFragments.Add(Fragment);
        }
        
        ExecuteInjectables(ObjectFragments);
        ExecuteInitializables(ObjectFragments);
        ExecuteTickables(ObjectFragments);
    }
}
