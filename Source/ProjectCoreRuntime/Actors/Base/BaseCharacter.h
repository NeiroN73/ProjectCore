// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UComponentsContainer;

UCLASS(Abstract)
class PROJECTCORERUNTIME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	
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

	void GatherDefaultComponentsInContainer();
};
