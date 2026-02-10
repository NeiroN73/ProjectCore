// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(Abstract)
class PROJECTCORERUNTIME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag Tag;

	public:
	FGameplayTag GetTag();
	ABaseCharacter();
};
