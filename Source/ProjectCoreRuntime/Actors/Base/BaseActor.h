// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

class UComponentsContainer;

UCLASS(Abstract)
class PROJECTCORERUNTIME_API ABaseActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag Tag;

public:
	FGameplayTag GetTag();
	virtual void Construct() {}
	virtual void Initialize() {}

	UComponentsContainer* GetComponentsContainer();
	void SetComponentsContainer(UComponentsContainer* InComponentsContainer);

private:
	UPROPERTY()
	TObjectPtr<UComponentsContainer> ComponentsContainer;
};
