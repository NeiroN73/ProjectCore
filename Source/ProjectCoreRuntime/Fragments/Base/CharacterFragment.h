// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Fragment.h"
#include "CharacterFragment.generated.h"

class ACharacterHandler;

UCLASS(Abstract)
class PROJECTCORERUNTIME_API UCharacterFragment : public UFragment
{
	GENERATED_BODY()

public:
	virtual void Initialize(ACharacterHandler* InCharacter, AController* InController);

protected:
	UPROPERTY()
	TWeakObjectPtr<ACharacterHandler> Character;
	UPROPERTY()
	TWeakObjectPtr<AController> Controller;
};
