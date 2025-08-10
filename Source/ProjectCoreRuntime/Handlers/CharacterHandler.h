// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectCoreRuntime/EditorUtils/CustomId.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentMacros.h"
#include "ProjectCoreRuntime/Handlers/Base/Handlerable.h"
#include "ProjectCoreRuntime/Services/Base/Fragmentable.h"
#include "ProjectCoreRuntime/TableConfigs/HandlersTableData.h"
#include "CharacterHandler.generated.h"

class AItemHandler;

UCLASS()
class PROJECTCORERUNTIME_API ACharacterHandler : public ACharacter,
public IHandlerable,
public IFragmentable
{
	GENERATED_BODY()
	FRAGMENTABLE_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Id")
	FCustomId Id;
	
	FHandlersTableData* Data;

	ACharacterHandler();

private:
	virtual FName GetId() override;

public:
	virtual void BuildFragments() override {}
	virtual void SetItemInSlot(AItemHandler* ItemHandler) {}
};
