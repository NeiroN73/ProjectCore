// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "InstallerGameMode.h"

AInstallerGameMode::AInstallerGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInstallerGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (auto CurrentWorld = GetWorld())
	{
		World = CurrentWorld;
	}
}
