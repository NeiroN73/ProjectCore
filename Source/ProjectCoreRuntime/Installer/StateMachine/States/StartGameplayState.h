// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerState.h"
#include "UObject/Object.h"
#include "ProjectCoreRuntime/Services/LevelsService.h"
#include "StartGameplayState.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UStartGameplayState : public UInstallerState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;

private:
	UPROPERTY()
	TWeakObjectPtr<ULevelsService> LevelsService;
	UPROPERTY()
	TWeakObjectPtr<UAssetsService> AssetsLoaderService;
};
