// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Config.h"
#include "ProjectCoreRuntime/Utils/JsonStructSerializer.h"
#include "UObject/Object.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonConfig.generated.h"

UCLASS(Abstract)
class PROJECTCORERUNTIME_API UJsonConfig : public UConfig
{
	GENERATED_BODY()

#if WITH_EDITORONLY_DATA
protected:
	UPROPERTY(EditAnywhere, meta = (RelativeToGameDir))
	FFilePath JsonPath;
	
	virtual void ReadJson() {}
	virtual void WriteJson() {}

	template<typename TParams = FJsonParams>
	TParams ReadStructFromJson()
	{
		const FString FullPath = GetFullJsonPath();
		return UJsonStructSerializer::ReadStructFromJson<TParams>(FullPath);
	}
	
	template<typename TParams = FJsonParams>
	void WriteStructToJson(TParams Params)
	{
		const FString FullPath = GetFullJsonPath();
		UJsonStructSerializer::WriteStructToJson(FullPath, Params);
	}

	FString GetFullJsonPath() const
	{
		if (JsonPath.FilePath.IsEmpty())
			return FString();
		
		return FPaths::ConvertRelativePathToFull(JsonPath.FilePath);
	}

	virtual void PostLoad() override;
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
#endif
};