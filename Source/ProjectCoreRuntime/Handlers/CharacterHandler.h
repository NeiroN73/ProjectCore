// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectCoreRuntime/EditorUtils/CustomId.h"
#include "ProjectCoreRuntime/Handlers/Base/Handlerable.h"
#include "ProjectCoreRuntime/TableConfigs/HandlersTableData.h"
#include "CharacterHandler.generated.h"

UCLASS(Abstract)
class PROJECTCORERUNTIME_API ACharacterHandler : public ACharacter,
public IHandlerable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Id")
	FCustomId Id;

	ACharacterHandler();

private:
	virtual FName GetId() override;
};
