// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "PawnHandler.h"


APawnHandler::APawnHandler()
{
	PrimaryActorTick.bCanEverTick = false;
}

FName APawnHandler::GetId()
{
	return Id;
}
