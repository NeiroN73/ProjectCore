// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ActorPool.h"

void UActorPool::Return(APoolableActor* Handler)
{
	if (Handler)
	{
		Handler->Return();
	}
}

void UActorPool::Release()
{
	for (auto Handler : Pool)
	{
		if (Handler)
		{
			Handler->Return();
			Handler->Destroy();
		}
	}
	Pool.Empty();
	PoolContainer->Destroy();
}