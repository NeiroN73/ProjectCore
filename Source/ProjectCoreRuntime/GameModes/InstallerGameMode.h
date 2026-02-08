// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InstallerGameMode.generated.h"

class UInstallerScope;
class UProjectInstallerScope;
class UConfigs;
class UTickService;
class UInstallerContainer;

UCLASS()
class PROJECTCORERUNTIME_API AInstallerGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UInstallerContainer> InstallerContainer;
	UPROPERTY()
	TWeakObjectPtr<UTickService> TickService;
	
	void InitializeScope(UConfigs* Configs = nullptr, TSubclassOf<UInstallerScope> ScopeClass = nullptr);
	void InitializeInjectables();
	void InitializeInitializables();
	void InitializeWorldables();
	void InitializeTickables();
	
public:
	AInstallerGameMode();
	virtual void Tick(float DeltaTime) override;
};
