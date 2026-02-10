// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "PoolableActor.h"


APoolableActor::APoolableActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APoolableActor::Get()
{
	IObjectPoolable::Get();
}

void APoolableActor::Return()
{
	IObjectPoolable::Return();
}

void APoolableActor::Release()
{
	IObjectPoolable::Release();
}
