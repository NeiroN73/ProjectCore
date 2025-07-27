// Fill out your copyright notice in the Description page of Project Settings.


#include "InstallerScope.h"

void UInstallerScope::Configure(UInstallerContainer* InContainer)
{
	Container = InContainer;
}

UInstallerContainer* UInstallerScope::GetContainer()
{
	return Container;
}
