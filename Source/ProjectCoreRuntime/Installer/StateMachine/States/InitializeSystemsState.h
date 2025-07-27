// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerState.h"
#include "UObject/Object.h"
#include "InitializeSystemsState.generated.h"

class UTickService;
class IInitializable;
class IInjectable;
class ITickable;
class IFragmentable;

UCLASS()
class PROJECTCORERUNTIME_API UInitializeSystemsState : public UInstallerState
{
	GENERATED_BODY()
	
public:
	virtual void Enter() override;

private:
	TArray<IInjectable*> Injectables;
	TArray<IInitializable*> Initializables;
	TArray<ITickable*> Tickables;
	TArray<IFragmentable*> Fragmentables;
	
	void InitializeSystems();
};