// Fill out your copyright notice in the Description page of Project Settings.


#include "ServiceLocator.h"

TWeakObjectPtr<UInstallerContainer> FServiceLocator::Container = nullptr;

void FServiceLocator::SetContainer(UInstallerContainer* InContainer)
{
	Container = InContainer;
}
