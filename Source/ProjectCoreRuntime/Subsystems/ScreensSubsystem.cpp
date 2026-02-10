// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ScreensSubsystem.h"

void UScreensSubsystem::Close()
{
	if (ScreensStack.Num() > 0)
	{
		auto ViewObject = ScreensStack.Pop();
		ViewObject->SetVisibility(ESlateVisibility::Collapsed);
		
		if (auto View = Cast<UScreen>(ViewObject))
		{
			View->Close();
		}
	}
}

void UScreensSubsystem::Inject()
{
	ViewFactory = GetGameInstance()->GetSubsystem<UScreensFactory>();
}
