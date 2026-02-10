// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ScreensFactory.h"


void UScreensFactory::InitializeView(UUserWidget* Widget)
{
	if (auto View = Cast<IView>(Widget))
	{
		View->BuildViewModel(ViewModelFactory.Get());
	}
}
