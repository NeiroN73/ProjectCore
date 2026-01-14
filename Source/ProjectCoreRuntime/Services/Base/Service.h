// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Installer/Worldable.h"
#include "Service.generated.h"

class UInstallerContainer;
class USaveState;

UCLASS(Abstract)
class PROJECTCORERUNTIME_API UService : public UObject,
public IWorldable
{
	GENERATED_BODY()

public:
	virtual void WorldChanged(UWorld* NewWorld) override;

	UPROPERTY()
	TObjectPtr<UWorld> World;
};
