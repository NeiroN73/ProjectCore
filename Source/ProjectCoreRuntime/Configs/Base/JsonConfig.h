// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Utils/JsonStructSerializer.h"
#include "UObject/Object.h"
#include "JsonConfig.generated.h"

UCLASS(Abstract)
class PROJECTCORERUNTIME_API UJsonConfig : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FFilePath JsonPath;

	UFUNCTION(CallInEditor)
	virtual void ReadJson() {}

	UFUNCTION(CallInEditor)
	virtual void WriteJson() {}

	template<typename TParams = FJsonParams>
	TParams ReadStructFromJson()
	{
		return UJsonStructSerializer::ReadStructFromJson<TParams>(JsonPath.FilePath);
	}
	
	template<typename TParams = FJsonParams>
	void WriteStructToJson(TParams Params)
	{
		UJsonStructSerializer::WriteStructToJson(JsonPath.FilePath, Params);
	}
};
