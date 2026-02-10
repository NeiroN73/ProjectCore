// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseFactory.generated.h"

class UComponentsFactory;
class UComponentsContainer;
class UInstallerContainer;

UCLASS()
class PROJECTCORERUNTIME_API UBaseFactory : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TWeakObjectPtr<UComponentsFactory> ComponentsFactory;
	UPROPERTY()
	TArray<TObjectPtr<UComponentsContainer>> ComponentsContainers; 
};
