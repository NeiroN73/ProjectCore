// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SavingSubsystem.generated.h"

class USaveState;
class ISavable;
class USaveGame;

UCLASS()
class PROJECTCORERUNTIME_API USavingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Save();
	void Load();

private:
	UPROPERTY()
	TArray<TObjectPtr<USaveState>> States;
	
	void OnSaved(const FString& SlotName, int32 UserIndex, bool bSuccess);
	void OnLoaded(const FString& SlotName, int32 UserIndex, USaveGame* SaveGame);
};
