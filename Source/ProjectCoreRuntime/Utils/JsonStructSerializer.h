// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "UObject/Object.h"
#include "JsonStructSerializer.generated.h"

USTRUCT()
struct FJsonParams
{
	GENERATED_BODY()
};

UCLASS()
class PROJECTCORERUNTIME_API UJsonStructSerializer : public UObject
{
	GENERATED_BODY()

public:
	template<typename TJsonParams = FJsonParams>
	static TJsonParams ReadStructFromJson(FString JsonPath)
	{
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*JsonPath))
		{
			return TJsonParams();
		}
		
		if (!FFileHelper::LoadFileToString(JsonPath, *JsonPath))
		{
			return TJsonParams();
		}
		
		TSharedPtr<FJsonObject> JsonObject;
		auto JsonReader = TJsonReaderFactory<>::Create(JsonPath);

		if (!FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			return TJsonParams();
		}

		TJsonParams JsonParams;
		if (!FJsonObjectConverter::JsonObjectToUStruct<TJsonParams>(JsonObject.ToSharedRef(), &JsonParams))
		{
			return TJsonParams();
		}

		return JsonParams;
	}

	template<typename TJsonParams = FJsonParams>
	static void WriteStructToJson(FString InJsonPath, TJsonParams InJsonParams)
	{
		auto JsonObject = FJsonObjectConverter::UStructToJsonObject(InJsonParams);
		if (JsonObject == nullptr)
		{
			return;
		}
		
		FString JsonString;
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*InJsonPath))
		{
			return;
		}

		auto JsonWriter = TJsonWriterFactory<>::Create(&JsonString);

		if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter))
		{
			return;
		}
		
		if (!FFileHelper::SaveStringToFile(JsonString, *InJsonPath))
		{
			return;
		}
	}
};
