// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ReturnHistoryElement.h"

void UReturnHistoryElement::Execute()
{
	State = EElementState::Completed;
}
