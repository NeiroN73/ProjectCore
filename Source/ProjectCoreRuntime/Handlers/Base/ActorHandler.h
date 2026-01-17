// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Handlerable.h"
#include "GameFramework/Actor.h"
#include "ProjectCoreRuntime/EditorUtils/CustomId.h"
#include "ActorHandler.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API AActorHandler : public AActor,
public IHandlerable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FCustomId Id;

private:
	virtual FName GetId() override;
};
