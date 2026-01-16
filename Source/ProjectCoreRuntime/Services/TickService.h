// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Service.h"
#include "Base/Tickable.h"
#include "TickService.generated.h"

class UFragmentsFactory;

UCLASS()
class PROJECTCORERUNTIME_API UTickService : public UService
{
	GENERATED_BODY()

public:
	void OnTick(float DeltaSeconds);
	void RegisterTick(ITickable* Tickable);

private:
	TArray<ITickable*> Tickables;
};
