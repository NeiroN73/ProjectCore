// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SlateWrapperTypes.h"
#include "ProjectCoreRuntime/Factories/ScreensFactory.h"
#include "ProjectCoreRuntime/Interfaces/Injectable.h"
#include "ProjectCoreRuntime/UI/Base/Screen.h"
#include "ScreensSubsystem.generated.h"

class UScreensFactory;

UCLASS()
class PROJECTCORERUNTIME_API UScreensSubsystem : public UGameInstanceSubsystem,
public IInjectable
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TWeakObjectPtr<UScreensFactory> ViewFactory;

	UPROPERTY()
	TMap<TSubclassOf<UScreen>, TObjectPtr<UScreen>> ScreensByClass;

	UPROPERTY()
	TArray<TObjectPtr<UScreen>> ScreensStack;

public:
	UPROPERTY()
	TObjectPtr<UScreen> CurrentScreen;
	
	void Close();
	
	virtual void Inject() override;
	
	template<class TScreen = UScreen>
	void Open(TSubclassOf<UScreen> InClass = TScreen::StaticClass())
	{
		if (auto FoundScreen = ScreensByClass.FindRef(InClass))
		{
			if (auto CastScreen = Cast<TScreen>(FoundScreen))
			{
				CurrentScreen = CastScreen;
			}
		}
		else
		{
			CurrentScreen = ViewFactory->CreateToViewport<TScreen>();
			if (CurrentScreen)
			{
				ScreensByClass.Add(InClass, CurrentScreen);
			}
		}

		CurrentScreen->SetVisibility(ESlateVisibility::Visible);
		CurrentScreen->Open();
	
		ScreensStack.Push(CurrentScreen);
	}
};
