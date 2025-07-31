// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreInstallerScope.h"

#include "ServiceLocator.h"
#include "ProjectCoreRuntime/Configs/Base/Configs.h"
#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Factories/FragmentsFactory.h"
#include "ProjectCoreRuntime/Factories/PoolsFactory.h"
#include "ProjectCoreRuntime/Factories/ViewModelsFactory.h"
#include "ProjectCoreRuntime/Factories/ScreensFactory.h"
#include "ProjectCoreRuntime/Factories/ViewsFactory.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Services/HistoryService.h"
#include "ProjectCoreRuntime/Services/LevelsService.h"
#include "ProjectCoreRuntime/Services/TickService.h"
#include "ProjectCoreRuntime/Services/SavingService.h"
#include "ProjectCoreRuntime/Services/ScreensService.h"
#include "ProjectCoreRuntime/SaveStates/HistorySaveState.h"
#include "ProjectCoreRuntime/Services/PreloadsService.h"
#include "ProjectCoreRuntime/Services/TweensService.h"


void UCoreInstallerScope::Configure(UInstallerContainer* InContainer)
{
	Super::Configure(InContainer);
	
	StateMachine = Container->Resolve<UInstallerStateMachine>();
	
	RegisterConfigs();
	RegisterTableConfigs();
	RegisterSaveStates();
	RegisterFactories();
	RegisterServices();
}

void UCoreInstallerScope::RegisterConfigs()
{
	auto Configs = Cast<UConfigs>(StateMachine->LoadedConfigsHandler->GetLoadedAsset())->Configs;
	for (const auto Config : Configs)
	{
		Register(Config);
	}
}

void UCoreInstallerScope::RegisterTableConfigs()
{
	auto TableConfigs =
		Cast<UConfigs>(StateMachine->LoadedConfigsHandler->GetLoadedAsset())->TableConfigs;
	for (auto TableConfig : TableConfigs)
	{
		StateMachine->InstallerContainer->RegisterTableConfig(TableConfig);
	}
}

void UCoreInstallerScope::RegisterSaveStates()
{
	Register<UHistorySaveState>();
}

void UCoreInstallerScope::RegisterFactories()
{
	Register<UViewModelsFactory>();
	Register<UScreensFactory>();
	Register<UHandlersFactory>();
	Register<UPoolsFactory>();
	Register<UFragmentsFactory>();
	Register<UViewsFactory>();
}

void UCoreInstallerScope::RegisterServices()
{
	Register(StateMachine->AssetsLoaderService);
	
	Register<USavingService>();
	Register<UScreensService>();
	Register<ULevelsService>();
	Register<UTickService>();
	Register<UHandlersService>();
	Register<UHistoryService>();
	Register<UPreloadsService>();
	Register<UTweensService>();
}