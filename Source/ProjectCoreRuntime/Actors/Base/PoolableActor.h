// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "ObjectPoolable.h"
#include "PoolableActor.generated.h"

UCLASS(Abstract)
class PROJECTCORERUNTIME_API APoolableActor : public ABaseActor,
public IObjectPoolable
{
	GENERATED_BODY()

public:
	APoolableActor();
	virtual void Get() override;
	virtual void Return() override;
	virtual void Release() override;
};
