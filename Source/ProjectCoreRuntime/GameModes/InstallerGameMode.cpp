// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "InstallerGameMode.h"

AInstallerGameMode::AInstallerGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInstallerGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
