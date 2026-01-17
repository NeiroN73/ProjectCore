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
	void ExecuteInjectables(TArray<UObject*>& Injectables);
	void ExecutePreInitializables(TArray<UObject*>& PreInitializables);
	void ExecuteInitializables(TArray<UObject*>& Initializables);
	void ExecuteTickables(TArray<UObject*>& Tickables);
	void ExecuteFragmentables(TArray<UObject*>& Fragmentables);
    
	void ExecuteInjectable(UObject* Object);
	void ExecutePreInitializable(UObject* Object);
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
