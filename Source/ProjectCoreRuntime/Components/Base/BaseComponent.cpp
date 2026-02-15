// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "BaseComponent.h"

UBaseComponent::UBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	SetTickEnable(false);
}

void UBaseComponent::SetTickEnable(bool bEnable)
{
	PrimaryComponentTick.SetTickFunctionEnable(bEnable);
}
