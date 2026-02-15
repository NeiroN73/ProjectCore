// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/TableData.h"
#include "HandlersTableData.generated.h"

USTRUCT()
struct PROJECTCORERUNTIME_API FHandlersTableData : public FTableData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Class;
}; 