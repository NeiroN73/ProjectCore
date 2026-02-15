// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseComponent.generated.h"

class UComponentsContainer;

UCLASS(Abstract)
class PROJECTCORERUNTIME_API UBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBaseComponent();
	virtual void Inject() {}
	virtual void Initialize() {}
	virtual void Construct() {}
	virtual void InjectComponentsContainer(UComponentsContainer* InComponentsContainer) {}
	
	virtual void BeginPlay() override;
	void SetTickEnable(bool bEnable);
};
