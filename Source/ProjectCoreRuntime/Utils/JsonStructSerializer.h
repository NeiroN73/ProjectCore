// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "Logger.h"
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
			LOG_MESSAGE(FString::Printf(TEXT("File does not exist at path: %s"), *JsonPath));
			return TJsonParams();
		}

		FString JsonString;
		if (!FFileHelper::LoadFileToString(JsonString, *JsonPath))
		{
			LOG_MESSAGE(FString::Printf(TEXT("Failed to load file: %s"), *JsonPath));
			return TJsonParams();
		}

		TSharedPtr<FJsonObject> JsonObject;
		auto JsonReader = TJsonReaderFactory<>::Create(JsonString);

		if (!FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			LOG_MESSAGE(TEXT("Failed to deserialize JSON"));
			return TJsonParams();
		}

		TJsonParams JsonParams;
		if (!FJsonObjectConverter::JsonObjectToUStruct<TJsonParams>(JsonObject.ToSharedRef(), &JsonParams))
		{
			LOG_MESSAGE(TEXT("Failed to convert JSON to struct"));
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
			LOG_MESSAGE(TEXT("Failed to convert struct to JSON object"));
			return;
		}

		FString JsonString;
		auto JsonWriter = TJsonWriterFactory<>::Create(&JsonString);

		if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter))
		{
			LOG_MESSAGE(TEXT("Failed to serialize JSON object to string"));
			return;
		}

		if (!FFileHelper::SaveStringToFile(JsonString, *InJsonPath))
		{
			LOG_MESSAGE(FString::Printf(TEXT("Failed to save JSON to file: %s"), *InJsonPath));
			return;
		}
	}
};