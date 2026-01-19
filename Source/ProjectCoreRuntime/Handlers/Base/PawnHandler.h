// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Handlerable.h"
#include "GameFramework/Pawn.h"
#include "ProjectCoreRuntime/Services/Base/Fragmentable.h"
#include "PawnHandler.generated.h"

class UFragmentsContainer;
class UFragmentsFactory;

UCLASS()
class PROJECTCORERUNTIME_API APawnHandler : public APawn,
public IHandlerable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FGameplayTag Tag;

	UPROPERTY()
	TObjectPtr<UFragmentsContainer> FragmentsContainer;
	
	APawnHandler();
};
