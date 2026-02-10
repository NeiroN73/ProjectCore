// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseObjectPool.h"
#include "ProjectCoreRuntime/Actors/Base/PoolableActor.h"
#include "ProjectCoreRuntime/Factories/ActorsFactory.h"
#include "UObject/Object.h"
#include "ActorPool.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UActorPool : public UBaseObjectPool
{
	GENERATED_BODY()

public:
	template<typename TActor = APoolableActor>
	void Create(AActor* PoolsContainer, int32 Size)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Name = FName("PoolContainer");
		PoolContainer = GetWorld()->SpawnActor<AActor>(SpawnParams);
		USceneComponent* PoolSceneComponent = NewObject<USceneComponent>(PoolContainer);
		PoolContainer->SetRootComponent(PoolSceneComponent);
		PoolContainer->AttachToActor(PoolsContainer, FAttachmentTransformRules::KeepWorldTransform);
		Class = TActor::StaticClass();
		
		for (int32 i = 0; i < Size; i++)
		{
			Get<TActor>();
		}
	}

	template<typename TActor = APoolableActor>
	TObjectPtr<TActor> Get()
	{
		for (auto Actor : Pool)
		{
			if (Actor && Actor->IsHidden())
			{
				Actor->Get();
				return Cast<TActor>(Actor);
			}
		}
		auto NewActor = ActorsFactory->SpawnActor<TActor>();
		NewActor->Get();
		Pool.Add(NewActor);
		NewActor->AttachToActor(PoolContainer, FAttachmentTransformRules::KeepWorldTransform);
		return NewActor;
	}

	void Return(APoolableActor* Actor);
	void Release();

private:
	UPROPERTY()
	TArray<TObjectPtr<APoolableActor>> Pool;

	UPROPERTY()
	TWeakObjectPtr<UActorsFactory> ActorsFactory;

	UPROPERTY()
	TObjectPtr<AActor> PoolContainer;

	UPROPERTY()
	TSubclassOf<APoolableActor> Class;
};
