// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/SaveState.h"
#include "HistorySaveState.generated.h"

class UHistoryElement;
class UBaseHistoryElement;
class UHistoryConfig;

UCLASS()
class PROJECTCORERUNTIME_API UHistorySaveState : public USaveState
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TSet<TObjectPtr<UHistoryElement>> CurrentElements;
	UPROPERTY()
	TSet<TObjectPtr<UHistoryElement>> AllElements;
	
	virtual void Read() override;
	virtual void Write() override;
	virtual void Initialize();

	void GatherElementsRecursive(const UBaseHistoryElement* ParentElement, TSet<UHistoryElement*>& OutElements);
	void GatherCurrentElementsRecursive(const UBaseHistoryElement* ParentElement);
	void UpdateCurrentElements();

private:
	UPROPERTY()
	TWeakObjectPtr<UHistoryConfig> HistoryConfig;
};
