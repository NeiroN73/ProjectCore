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

	void RegisterConfigs();
	void RegisterSaveStates();
	void RegisterTableConfigs();
	void RegisterServices();
	void RegisterFactories();
};
