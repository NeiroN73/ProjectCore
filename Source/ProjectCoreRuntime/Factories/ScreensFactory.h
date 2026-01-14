// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseFactory.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "ProjectCoreRuntime/Configs/ScreensConfig.h"
#include "ProjectCoreRuntime/Services/AssetsService.h"
#include "ProjectCoreRuntime/UI/Base/Screen.h"
#include "ScreensFactory.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UScreensFactory : public UBaseFactory
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TWeakObjectPtr<UScreensConfig> ScreensConfig;
	UPROPERTY()
	TWeakObjectPtr<UAssetsService> AssetsLoaderService;
	UPROPERTY()
	TWeakObjectPtr<UViewModelsFactory> ViewModelFactory;
	
public:
	virtual void Inject(UInstallerContainer* Container) override;
	
	template<class TScreen = UScreen>
	TScreen* Create()
	{
		if (auto ViewClass = ScreensConfig->GetScreenClass<TScreen>())
		{
			if (auto View = CreateWidget<TScreen>(World, ViewClass))
			{
				InitializeView(View);
				return View;
			}
		}

		return nullptr;
	}

	template<class TScreen = UScreen>
	TScreen* CreateToViewport()
	{
		if (auto View = Create<TScreen>())
		{
			View->AddToViewport();
			return View;
		}
		return nullptr;
	}

	void InitializeView(UUserWidget* Widget);
};
