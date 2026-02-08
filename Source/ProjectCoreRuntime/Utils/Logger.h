// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define LOG_MESSAGE(Message) FLogger::ShowMessage(Message, TEXT(__FUNCTION__))

class PROJECTCORERUNTIME_API FLogger
{
public:
	static void ShowMessage(const FString& Message, const FString& Function = TEXT(""));
	static void ShowNotification(const FString& Message);
};
