// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstallerGameSubsystem.generated.h"

class UInstallerScope;
class UInstallerContainer;

UCLASS()
class PROJECTCORERUNTIME_API UInstallerGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<UInstallerContainer> InstallerContainer;
	UPROPERTY()
	TObjectPtr<UInstallerScope> InstallerScope;
};
