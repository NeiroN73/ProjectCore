#pragma once

#include "ProjectCoreRuntime/Fragments/Base/Fragment.h"
#include "ProjectCoreRuntime/DependencyInjection/ServiceLocator.h"
#include "ProjectCoreRuntime/Factories/FragmentsFactory.h"

#define FRAGMENTABLE_BODY() \
private: \
	UPROPERTY() \
	TObjectPtr<UFragmentsFactory> FragmentsFactory; \
	UPROPERTY() \
	TMap<TSubclassOf<UFragment>, TObjectPtr<UFragment>> Fragments; \
public: \
	template<typename TFragment = UFragment> \
	TFragment* GetFragment(TSubclassOf<TFragment> Class = TFragment::StaticClass()) \
	{ \
		if (auto Fragment = Fragments.Find(Class)) \
 		{ \
			return Cast<TFragment>(*Fragment); \
		} \
		return nullptr; \
	} \
	template<typename TFragment = UFragment> \
	bool HasFragment(TSubclassOf<TFragment> Class = TFragment::StaticClass()) \
	{ \
		if (auto Fragment = Fragments.Contains(Class)) \
		{ \
			return true; \
		} \
		return false; \
	} \
	template<typename TFragment = UFragment> \
	TFragment* TryAddFragment(TSubclassOf<TFragment> Class = TFragment::StaticClass()) \
	{ \
		if (!Fragments.Contains(Class)) \
		{ \
	        auto Fragment = FServiceLocator::Resolve<UFragmentsFactory>()->Create<TFragment>(); \
			Fragments.Add(Class, Fragment); \
			return Fragment; \
		} \
		return nullptr; \
	} \
	template<typename TFragment = UFragment> \
	void RemoveFragment(TSubclassOf<TFragment> Class = TFragment::StaticClass()) \
	{ \
 		Fragments.Remove(Class); \
	}