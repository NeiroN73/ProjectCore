// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ViewsFactory.h"

#include "ViewModelsFactory.h"
#include "ProjectCoreRuntime/DependencyInjection/InstallerContainer.h"
#include "ProjectCoreRuntime/UI/Base/View.h"

void UViewsFactory::Inject(UInstallerContainer* Container)
{
	Super::Inject(Container);
	
	ViewModelsFactory = Container->Resolve<UViewModelsFactory>();
}

void UViewsFactory::InitializeView(UUserWidget* Widget)
{
	if (auto View = Cast<IView>(Widget))
	{
		View->BuildViewModel(ViewModelsFactory);
	}
}
