// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProjectCoreRuntime/GameModes/Base/InstallerGameMode.h"
#include "InstallerStateMachine.generated.h"

class UInstallerScope;
class UAssetsService;
struct FStreamableHandle;
class UInstallerContainer;
class UInstallerState;

UCLASS()
class PROJECTCORERUNTIME_API UInstallerStateMachine : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<TObjectPtr<UInstallerScope>> InstallerScopes;
	UPROPERTY()
	TObjectPtr<UInstallerContainer> InstallerContainer;
	UPROPERTY()
	TObjectPtr<UAssetsService> AssetsLoaderService;
	TSharedPtr<FStreamableHandle> LoadedConfigsHandler;
	
	void Initialize(TArray<UInstallerState*> NewStates);
	void Tick(float DeltaSeconds);
	void NextState();

private:
	TQueue<TObjectPtr<UInstallerState>> States;
	UPROPERTY()
	TObjectPtr<UInstallerState> CurrentState;
};
