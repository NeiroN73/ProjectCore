// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstallerContainer.h"
#include "InstallerScope.h"
#include "CoreInstallerScope.generated.h"

class UInstallerStateMachine;

UCLASS()
class PROJECTCORERUNTIME_API UCoreInstallerScope : public UInstallerScope
{
	GENERATED_BODY()

public:
	virtual void Configure(UInstallerContainer* InContainer) override;
	
private:
	UPROPERTY()
	TObjectPtr<UInstallerStateMachine> StateMachine;

public:
	virtual void RegisterConfigs();
	virtual void RegisterSaveStates();
	virtual void RegisterTableConfigs();
	virtual void RegisterServices();
	virtual void RegisterFactories();
};
