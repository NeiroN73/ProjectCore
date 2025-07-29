// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstallerContainer.h"

class PROJECTCORERUNTIME_API FServiceLocator
{
private:
	static TWeakObjectPtr<UInstallerContainer> Container;

public:
	static void SetContainer(UInstallerContainer* InContainer);
	
	template<typename T>
	static T Resolve()
	{
		if (Container.IsValid())
		{
			return Container->Resolve<T>();
		}
		return nullptr;
	}
};
