// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InstallerStateMachine.generated.h"

class UInstallerState;

UCLASS()
class PROJECTCORERUNTIME_API UInstallerStateMachine : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(TArray<UInstallerState*> NewStates);
	void NextState();

private:
	TQueue<TObjectPtr<UInstallerState>> States;
	UPROPERTY()
	TObjectPtr<UInstallerState> CurrentState;
};
