// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Factories/ComponentsFactory.h"
#include "UObject/Object.h"
#include "ComponentsContainer.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UComponentsContainer : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TMap<TObjectPtr<UClass>, TObjectPtr<UBaseComponent>> ComponentsByType;

public:
	template<class TComponent = UBaseComponent>
	TComponent* TryAddComponent(TComponent* NewComponent)
	{
		auto Class = TComponent::StaticClass();
		if (ComponentsByType.Add(Class, NewComponent))
		{
			return NewComponent;
		}
		return nullptr;
	}

	template<class TComponent = UBaseComponent>
	TComponent* TryAddComponentWithInterfaces(TComponent* InComponent, TArray<TSubclassOf<UInterface>> BaseInterfaces)
	{
		auto Class = TComponent::StaticClass();
		TComponent* NewComponent;

		if (auto Component = ComponentsByType.FindRef(Class))
		{
			NewComponent = Cast<TComponent>(Component);
		}
		else
		{
			NewComponent = InComponent;
		}
		
		for (auto BaseInterface : BaseInterfaces)
		{
			if (!ComponentsByType.Contains(BaseInterface))
			{
				if (ComponentsByType.Add(BaseInterface, NewComponent))
				{
					ComponentsByType.Add(Class, NewComponent);
				}
			}
		}
		
		return NewComponent;
	}

	template<class TComponent>
	TComponent* TryGetComponentInterface()
	{
		auto Class = TComponent::UClassType::StaticClass();
		if (auto Component = ComponentsByType.FindRef(Class))
		{
			if (auto CastComponent = Cast<TComponent>(Component))
			{
				return CastComponent;
			}
		}
		return nullptr;
	}

	template<class TComponent = UBaseComponent>
	TComponent* TryGetComponent(TSubclassOf<TComponent> Class = TComponent::StaticClass())
	{
		if (auto Component = ComponentsByType.FindRef(Class))
		{
			if (auto CastComponent = Cast<TComponent>(Component))
			{
				return CastComponent;
			}
		}
		return nullptr;
	}

	TArray<UBaseComponent*> GetComponents();
};
