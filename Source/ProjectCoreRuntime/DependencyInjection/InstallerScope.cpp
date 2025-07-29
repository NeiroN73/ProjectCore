// Fill out your copyright notice in the Description page of Project Settings.


#include "InstallerScope.h"

#include "InstallerContainer.h"

void UInstallerScope::Configure(UInstallerContainer* InContainer)
{
	Container = InContainer;
}

UInstallerContainer* UInstallerScope::GetContainer()
{
	return Container;
}

void UInstallerScope::Register(UObject* Object)
{
	Container->Register(Object);
}
