// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "HistoryCondition.h"

void UHistoryCondition::MarkCompleted()
{
	bCompleted = true;
	OnCompleted.ExecuteIfBound();
}
