// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoriesLocator.h"

TWeakObjectPtr<UInstallerContainer> FFactoriesLocator::Container = nullptr;

void FFactoriesLocator::SetContainer(UInstallerContainer* InContainer)
{
	Container = InContainer;
}
