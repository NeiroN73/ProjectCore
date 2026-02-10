// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseFactory.h"
#include "Blueprint/UserWidget.h"
#include "ViewsFactory.generated.h"

class UViewModelsFactory;

UCLASS()
class PROJECTCORERUNTIME_API UViewsFactory : public UBaseFactory
{
	GENERATED_BODY()

public:
	void InitializeView(UUserWidget* Widget);
	
	template<class TWidget = UUserWidget>
	TWidget* Create(TSubclassOf<TWidget> InClass = TWidget::StaticClass())
	{
		if (auto View = CreateWidget<TWidget>(GetWorld(), InClass))
		{
			InitializeView(View);
			return View;
		}

		return nullptr;
	}

private:
	UPROPERTY()
	TWeakObjectPtr<UViewModelsFactory> ViewModelsFactory;
};
