// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InstallerScope.generated.h"

class UInstallerContainer;

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
};
