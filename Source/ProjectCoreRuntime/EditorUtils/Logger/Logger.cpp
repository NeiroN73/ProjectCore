// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "Logger.h"

#include "Developer/MessageLog/Public/IMessageLogListing.h"
#include "Developer/MessageLog/Public/MessageLogModule.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

class FMessageLogModule;

void FLogger::ShowMessage(const FString& Message, const FString& Function)
{
	FString Prefix;
    
	if (!Function.IsEmpty())
	{
		Prefix = FString::Printf(TEXT("[%s] "), *Function);
	}
    
	FString FullMessage = Prefix + Message;
	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
    
	if (!MessageLogModule.IsRegisteredLogListing("Errors"))
	{
		FMessageLogInitializationOptions InitOptions;
		InitOptions.bShowInLogWindow = true;
		MessageLogModule.RegisterLogListing("Errors", FText::FromString("Errors"), InitOptions);
	}
    
	TSharedPtr<IMessageLogListing> LogListing = MessageLogModule.GetLogListing("Errors");
	LogListing->AddMessage(FTokenizedMessage::Create(EMessageSeverity::Error, FText::FromString(FullMessage)));
	MessageLogModule.OpenMessageLog("Errors");
}

void FLogger::ShowNotification(const FString& Message)
{
	FNotificationInfo Info(FText::FromString(Message));
	Info.ExpireDuration = 5;
	Info.bUseLargeFont = false;
	Info.bUseThrobber = true;
	Info.bFireAndForget = true;
	Info.bAllowThrottleWhenFrameRateIsLow = true;
    
	FSlateNotificationManager::Get().AddNotification(Info);
}

