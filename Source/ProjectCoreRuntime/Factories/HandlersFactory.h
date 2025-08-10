// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseFactory.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectCoreRuntime/Handlers/Base/ActorHandler.h"
#include "ProjectCoreRuntime/Services/HandlersService.h"
#include "ProjectCoreRuntime/TableConfigs/HandlersTableData.h"
#include "HandlersFactory.generated.h"

class UHandlersConfig;
class AGameplayGameMode;

DECLARE_DELEGATE_OneParam(FOnCharacterHandlerAdded, ACharacterHandler*)
DECLARE_DELEGATE_OneParam(FOnActorHandlerAdded, AActorHandler*)

UCLASS()
class PROJECTCORERUNTIME_API UHandlersFactory : public UBaseFactory
{
	GENERATED_BODY()

public:
	FOnCharacterHandlerAdded OnCharacterHandlerAdded;
	FOnActorHandlerAdded OnActorHandlerAdded;
	
	template<class TActor = AActor>
	TActor* SpawnHandler(FName Id = "", FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator)
	{
		auto Data = HandlersTableConfig->FindRow<FHandlersTableData>(Id, "");
		if (auto Handler = World->SpawnActor<TActor>(Data->Class, Location, Rotation))
		{
			InitializeHandler(Handler);
			return Handler;
		}
		
		return nullptr;
	}

	template<class TCharacter = ACharacterHandler>
	TCharacter* SpawnCharacterHandler(FName Id = "", FVector Location = FVector::ZeroVector,
		FRotator Rotation = FRotator::ZeroRotator)
	{
		auto Handler = SpawnHandler<TCharacter>(Id, Location, Rotation);
		InitializeCharacterHandler(Handler);

		if (auto PlayerController = UGameplayStatics::GetPlayerController(World, 0))
		{
			PlayerController->Possess(Handler);
		}

		return Handler;
	}

	void InitializeCharacterHandler(ACharacterHandler* Handler);
	void InitializeHandler(AActor* Actor);

	virtual void Inject(UInstallerContainer* Container) override;

private:
	UPROPERTY()
	TObjectPtr<UDataTable> HandlersTableConfig;
};