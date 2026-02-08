// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "UObject/Object.h"
#include "ProjectCoreRuntime/Installer/Worldable.h"
#include "BaseFactory.generated.h"

class UFragmentsFactory;
class UFragmentsContainer;
class UTickService;
class UInstallerContainer;

UCLASS()
class PROJECTCORERUNTIME_API UBaseFactory : public UObject,
public IInjectable,
public IWorldable
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UWorld> World;
	
	virtual void Inject(UInstallerContainer* Container) override;
	virtual void WorldChanged(UWorld* NewWorld) override;

protected:
	template<class TObject = UObject>
	void ExecuteInjectables(TArray<TObject*> Injectables)
	{
		for (auto Injectable : Injectables)
		{
			ExecuteInjectable(Cast<UObject>(Injectable));
		}
	}

	template<class TObject = UObject>
	void ExecuteInitializables(TArray<TObject*> Initializables)
	{
		for (auto Initializable : Initializables)
		{
			ExecuteInitializable(Cast<UObject>(Initializable));
		}
	}

	template<class TObject = UObject>
	void ExecuteTickables(TArray<TObject*> Tickables)
	{
		for (auto Tickable : Tickables)
		{
			ExecuteTickable(Cast<UObject>(Tickable));
		}
	}

	template<class TObject = UObject>
	void ExecuteFragmentables(TArray<TObject*> Fragmentables)
	{
		for (auto Fragmentable : Fragmentables)
		{
			ExecuteFragmentable(Cast<UObject>(Fragmentable));
		}
	}
    
	void ExecuteInjectable(UObject* Object);
	void ExecuteInitializable(UObject* Object);
	void ExecuteTickable(UObject* Object);
	void ExecuteFragmentable(UObject* Object);

private:
	UPROPERTY()
	TObjectPtr<UInstallerContainer> InstallerContainer;
	UPROPERTY()
	TWeakObjectPtr<UTickService> TickService;
	UPROPERTY()
	TWeakObjectPtr<UFragmentsFactory> FragmentsFactory;
	UPROPERTY()
	TArray<TObjectPtr<UFragmentsContainer>> FragmentsContainers; 
};
