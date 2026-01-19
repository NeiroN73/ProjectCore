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
	UPROPERTY()
	TMap<TObjectPtr<UClass>, TObjectPtr<UFragment>> FragmentsByType;

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
	TFragment* TryAddFragmentByInterfaces(TArray<TSubclassOf<UInterface>> BaseInterfaces)
	{
		auto Class = TFragment::StaticClass();
		auto Factory = FFactoriesLocator::Resolve<UFragmentsFactory>();
		TFragment* NewFragment;

		if (auto Fragment = FragmentsByType.FindRef(Class))
		{
			NewFragment = Cast<TFragment>(Fragment);
		}
		else
		{
			NewFragment = Factory->Create<TFragment>();
		}
		
		for (auto BaseInterface : BaseInterfaces)
		{
			if (!FragmentsByType.Contains(BaseInterface))
			{
				if (FragmentsByType.Add(BaseInterface, NewFragment))
				{
					FragmentsByType.Add(Class, NewFragment);
				}
			}
		}
		
		return NewFragment;
	}

	template<class TFragment>
	TFragment* TryGetFragmentInterface()
	{
		auto Class = TFragment::UClassType::StaticClass();
		if (auto Fragment = FragmentsByType.FindRef(Class))
		{
			if (auto CastFragment = Cast<TFragment>(Fragment))
			{
				return CastFragment;
			}
		}
		return nullptr;
	}

	template<class TFragment = UFragment>
	TFragment* TryGetFragment(TSubclassOf<TFragment> Class = TFragment::StaticClass())
	{
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
