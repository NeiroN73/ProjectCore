// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "HistoryTrigger.h"

void UHistoryTrigger::MarkTriggered()
{
	bTriggered = true;
	OnTriggered.ExecuteIfBound();
}
