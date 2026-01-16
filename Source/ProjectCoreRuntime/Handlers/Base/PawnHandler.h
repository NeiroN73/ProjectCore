// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Handlerable.h"
#include "GameFramework/Pawn.h"
#include "ProjectCoreRuntime/EditorUtils/CustomId.h"
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
	UPROPERTY(EditAnywhere, Category="Id")
	FCustomId Id;

	UPROPERTY()
	TObjectPtr<UFragmentsContainer> FragmentsContainer;
	
	APawnHandler();

	virtual FName GetId() override;
};
