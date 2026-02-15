// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UComponentsContainer;

UCLASS(Abstract)
class PROJECTCORERUNTIME_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	FGameplayTag GetTag();
	UComponentsContainer* GetComponentsContainer();
	void SetComponentsContainer(UComponentsContainer* InComponentsContainer);
	virtual void Construct() {}
	virtual void Initialize() {}

private:
	UPROPERTY(EditAnywhere)
	FGameplayTag Tag;
	UPROPERTY()
	TObjectPtr<UComponentsContainer> ComponentsContainer;
};
