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
	TWeakObjectPtr<UComponentsFactory> ComponentsFactory;
	
	UPROPERTY()
	TMap<TObjectPtr<UClass>, TObjectPtr<UActorComponent>> ComponentsByType;

public:
	template<class TComponent = UActorComponent>
	UComponentsContainer* TryAddComponent(TComponent* NewComponent)
	{
		if (ComponentsByType.Add(NewComponent->GetClass(), NewComponent))
		{
			return this;
		}
		return nullptr;
	}

	template<class TComponent = UActorComponent>
	UComponentsContainer* TryAddComponentWithInterfaces(TComponent* InComponent, TArray<TSubclassOf<UInterface>> BaseInterfaces)
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
		
		return this;
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

	template<class TComponent = UActorComponent>
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

	TArray<UActorComponent*> GetComponents();
	void Build();
	virtual void Construct();
	virtual void Initialize();
};
