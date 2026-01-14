// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Service.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "HistoryService.generated.h"

class UPreloadsService;
class UHistorySaveState;
class UHistoryConfig;

DECLARE_DELEGATE(FOnHistoryProgressed)

UCLASS()
class PROJECTCORERUNTIME_API UHistoryService : public UService,
public IInjectable
{
	GENERATED_BODY()

public:
	virtual void Inject(UInstallerContainer* InContainer) override;

	void TryProgress();
	void OnPreloadsLoaded();

private:
	UPROPERTY()
	TWeakObjectPtr<UHistorySaveState> HistorySaveState;
	UPROPERTY()
	TWeakObjectPtr<UInstallerContainer> Container;
	UPROPERTY()
	TWeakObjectPtr<UHistoryConfig> HistoryConfig;
	UPROPERTY()
	TWeakObjectPtr<UPreloadsService> PreloadsService;

public:
	FOnHistoryProgressed OnHistoryProgressed;
};
