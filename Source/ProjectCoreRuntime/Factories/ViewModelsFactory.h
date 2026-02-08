// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseFactory.h"
#include "ViewModelsFactory.generated.h"

class UViewModel;

UCLASS()
class PROJECTCORERUNTIME_API UViewModelsFactory : public UBaseFactory
{
	GENERATED_BODY()

public:
	template<class TViewModel = UViewModel>
	TViewModel* Create()
	{
		TViewModel* ViewModel = NewObject<TViewModel>();
		ExecuteInjectable(ViewModel);
		ExecuteInitializable(ViewModel);
		ExecuteTickable(ViewModel);
		return ViewModel;
	}
};
