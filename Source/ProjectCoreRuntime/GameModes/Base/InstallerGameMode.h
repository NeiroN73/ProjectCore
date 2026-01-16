// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InstallerGameMode.generated.h"

class UInstallerContainer;
class UTickService;
class UInstallerStateMachine;

UCLASS()
class PROJECTCORERUNTIME_API AInstallerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TObjectPtr<UInstallerStateMachine> StateMachine;
	UPROPERTY()
	TObjectPtr<UInstallerContainer> InstallerContainer;
	UPROPERTY()
	TWeakObjectPtr<UTickService> TickService;
	UPROPERTY()
	TObjectPtr<UWorld> World;

	virtual void BeginPlay() override;

public:
	AInstallerGameMode();
};
