// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Fragment.h"
#include "ProjectCoreRuntime/DependencyInjection/FactoriesLocator.h"
#include "ProjectCoreRuntime/Factories/FragmentsFactory.h"
#include "UObject/Object.h"
#include "FragmentsContainer.generated.h"

class UFragment;

UCLASS()
class PROJECTCORERUNTIME_API UFragmentsContainer : public UObject
{
	GENERATED_BODY()

private:
	TMap<TSubclassOf<UFragment>, TObjectPtr<UFragment>> FragmentsByType;

public:
	template<class TFragment = UFragment>
	TFragment* TryAddFragment()
	{
		auto Class = TFragment::StaticClass();
		auto Factory = FFactoriesLocator::Resolve<UFragmentsFactory>();
		auto NewFragment = Factory->Create<TFragment>();
		if (FragmentsByType.Add(Class, NewFragment))
		{
			return NewFragment;
		}
		return nullptr;
	}

	template<class TFragment = UFragment>
	TFragment* TryGetFragment()
	{
		auto Class = TFragment::StaticClass();
		if (auto Fragment = FragmentsByType.FindRef(Class))
		{
			if (auto CastFragment = Cast<TFragment>(Fragment))
			{
				return CastFragment;
			}
		}
		return nullptr;
	}

	TArray<UFragment*> GetFragments();
};
