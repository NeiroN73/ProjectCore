// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "PawnHandler.h"


APawnHandler::APawnHandler()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APawnHandler::BuildFragments()
{
}

FName APawnHandler::GetId()
{
	return Id;
}
