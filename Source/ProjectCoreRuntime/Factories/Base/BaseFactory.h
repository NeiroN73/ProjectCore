// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "UObject/Object.h"
#include "ProjectCoreRuntime/Installer/Worldable.h"
#include "BaseFactory.generated.h"

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
	void GetAllAccesses(UObject* Object);
	void GetAccessInjectable(UObject* Object);
	void GetAccessPreInitializable(UObject* Object);
	void GetAccessInitializable(UObject* Object);
	void GetAccessTickable(UObject* Object);
	void GetAccessFragmentable(UObject* Object);

private:
	UPROPERTY()
	TObjectPtr<UInstallerContainer> InstallerContainer;
	UPROPERTY()
	TObjectPtr<UTickService> TickService;
	UPROPERTY()
	TArray<TObjectPtr<UFragmentsContainer>> FragmentsContainers; 
};
