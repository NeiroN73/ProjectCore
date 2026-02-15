// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Interfaces/Initializable.h"
#include "ProjectCoreRuntime/Interfaces/Injectable.h"
#include "ProjectCoreRuntime/Interfaces/PreInitializable.h"
#include "UObject/Object.h"
#include "BaseFactory.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UBaseFactory : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override {}

protected:
	template<class TObject = UObject>
	void ExecuteInitialize(TObject* Object)
	{
		if (auto Initializable = Cast<IPreInitializable>(Object))
		{
			Initializable->PreInitialize();
		}
		if (auto Initializable = Cast<IInitializable>(Object))
		{
			Initializable->Initialize();
		}
	}

	template<class TObject = UObject>
	void ExecuteInject(TObject* Object)
	{
		if (auto Injectable = Cast<IInjectable>(Object))
		{
			Injectable->Inject();
		}
	}
};
