// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerState.h"
#include "UObject/Object.h"
#include "InitializeSystemsState.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UInitializeSystemsState : public UInstallerState
{
	GENERATED_BODY()
	
public:
	virtual void Enter() override;

private:
	void InitializeSystems();
};