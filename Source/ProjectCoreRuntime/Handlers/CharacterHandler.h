// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "ProjectCoreRuntime/Handlers/Base/Handlerable.h"
#include "CharacterHandler.generated.h"

UCLASS(Abstract)
class PROJECTCORERUNTIME_API ACharacterHandler : public ACharacter,
public IHandlerable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag Tag;

	public:
	FGameplayTag GetTag();
	ACharacterHandler();
};
