// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Interfaces/Injectable.h"
#include "HistorySubsystem.generated.h"

class UPreloadSubsystem;
class UHistorySaveState;
class UHistoryConfig;

DECLARE_DELEGATE(FOnHistoryProgressed)

UCLASS()
class PROJECTCORERUNTIME_API UHistorySubsystem : public UGameInstanceSubsystem,
public IInjectable
{
	GENERATED_BODY()

public:
	void TryProgress();
	void OnPreloadsLoaded();
	virtual void Inject() override;

private:
	UPROPERTY()
	TWeakObjectPtr<UHistorySaveState> HistorySaveState;
	UPROPERTY()
	TWeakObjectPtr<UHistoryConfig> HistoryConfig;
	UPROPERTY()
	TWeakObjectPtr<UPreloadSubsystem> PreloadsService;

public:
	FOnHistoryProgressed OnHistoryProgressed;
};
