// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ViewsFactory.h"

#include "ProjectCoreRuntime/UI/Base/View.h"

void UViewsFactory::InitializeView(UUserWidget* Widget)
{
	if (auto View = Cast<IView>(Widget))
	{
		View->BuildViewModel(ViewModelsFactory.Get());
	}
}
