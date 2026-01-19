// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Config.h"
#include "ProjectCoreRuntime/Utils/JsonStructSerializer.h"
#include "UObject/Object.h"
#include "JsonConfig.generated.h"

UCLASS(Abstract)
class PROJECTCORERUNTIME_API UJsonConfig : public UConfig
{
	GENERATED_BODY()

#if WITH_EDITORONLY_DATA
protected:
	UPROPERTY(EditAnywhere, Category="Json config")
	FFilePath JsonPath;

	UFUNCTION(CallInEditor, Category="Json config", DisplayName="Read from json")
	virtual void ReadJson() {}

	UFUNCTION(CallInEditor, Category="Json config", DisplayName="Write to json")
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
#endif
};
