// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "SavingSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectCoreRuntime/SaveData/Base/DataSaveGame.h"
#include "ProjectCoreRuntime/SaveStates/Base/SaveState.h"


void USavingSubsystem::Save()
{
	if (auto* SaveGame = Cast<UDataSaveGame>(UGameplayStatics::CreateSaveGameObject(UDataSaveGame::StaticClass())))
	{
		for (auto State : States)
		{
			State->SaveGame = SaveGame;
			State->Write();
		}

		UGameplayStatics::AsyncSaveGameToSlot(SaveGame, TEXT("SaveSlot"), 0,
			FAsyncSaveGameToSlotDelegate::CreateUObject(this, &USavingSubsystem::OnSaved));
	}
}

void USavingSubsystem::OnSaved(const FString& SlotName, int32 UserIndex, bool bSuccess)
{
	if (bSuccess)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Save successful!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Save failed!"));
	}
}

void USavingSubsystem::Load()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("SaveSlot"), 0))
	{
		UGameplayStatics::AsyncLoadGameFromSlot(TEXT("SaveSlot"), 0,
					FAsyncLoadGameFromSlotDelegate::CreateUObject(this, &USavingSubsystem::OnLoaded));
	}
	else
	{
		Save();
	}
}

void USavingSubsystem::OnLoaded(const FString& SlotName, int32 UserIndex, USaveGame* SaveGame)
{
	for (USaveState* State : States)
	{
		State->SaveGame = Cast<UDataSaveGame>(SaveGame);
		State->Read();
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Load successful!"));
}
