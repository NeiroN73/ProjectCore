// Copyright Floruit, Inc. All Rights Reserved.


#include "TickService.h"


void UTickService::OnTick(float DeltaSeconds)
{
	for (auto Tickable : Tickables)
	{
		if (Tickable)
		{
			Tickable->OnTick(DeltaSeconds);
		}
		else
		{
			Tickables.Remove(Tickable);
		}
	}
}

void UTickService::RegisterTick(ITickable* Tickable)
{
	if (Tickable != this)
	{
		Tickables.Add(Tickable);
	}
}
