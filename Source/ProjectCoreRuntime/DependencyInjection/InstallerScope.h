// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstallerContainer.h"
#include "UObject/Object.h"
#include "InstallerScope.generated.h"

class UConfigs;

UCLASS()
class PROJECTCORERUNTIME_API UInstallerScope : public UObject
{
	GENERATED_BODY()

public:
	virtual void Configure(UInstallerContainer* InContainer);
	UInstallerContainer* GetContainer();

protected:
	UPROPERTY()
	TObjectPtr<UInstallerContainer> Container;
	UPROPERTY()
	TWeakObjectPtr<UConfigs> Configs;

	void Register(UObject* Object);

	template<typename T>
	void Register()
	{
		Container->Register<T>();
	}
	
public:
	virtual void RegisterConfigs() {}
	virtual void RegisterSaveStates() {}
	virtual void RegisterTableConfigs() {}
	virtual void RegisterServices() {}
	virtual void RegisterFactories() {}

	void SetConfigs(UConfigs* InConfigs);
};
