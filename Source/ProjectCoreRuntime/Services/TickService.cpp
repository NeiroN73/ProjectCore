// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "TickService.h"


void UTickService::OnTick(float DeltaSeconds)
{
	for (auto Tickable : Tickables)
	{
		if (Tickable.Get())
		{
			Tickable->OnTick(DeltaSeconds);
		}
	}
}

void UTickService::RegisterTick(ITickable* Tickable)
{
	if (!Tickables.Contains(Tickable))
	{
		Tickables.Add(Tickable);
	}
}
