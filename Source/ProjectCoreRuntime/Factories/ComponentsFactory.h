// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseFactory.h"
#include "ProjectCoreRuntime/Components/Base/BaseComponent.h"
#include "ComponentsFactory.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UComponentsFactory : public UBaseFactory
{
	GENERATED_BODY()

public:
	template<typename TComponent = UBaseComponent>
	TComponent* Create()
	{
		auto Component = NewObject<TComponent>();
		return Component;
	}
};
