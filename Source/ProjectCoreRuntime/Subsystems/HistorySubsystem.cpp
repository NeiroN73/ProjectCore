// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "HistorySubsystem.h"

#include "ConfigsSubsystem.h"
#include "PreloadSubsystem.h"
#include "ProjectCoreRuntime/History/Actions/Base/HistoryAction.h"
#include "ProjectCoreRuntime/History/Base/Preloadable.h"
#include "ProjectCoreRuntime/History/Elements/HistoryElement.h"
#include "ProjectCoreRuntime/SaveStates/HistorySaveState.h"


void UHistorySubsystem::TryProgress()
{
	HistorySaveState->UpdateCurrentElements();

	TSet<FName> PreloadIds;
	for (auto Element : HistorySaveState->CurrentElements)
	{
		if (auto HistoryElement = Cast<UHistoryElement>(Element))
		{
			if (HistoryElement->bRootPreloadable)
			{
				TSet<UHistoryElement*> OutElements;
				HistorySaveState->GatherElementsRecursive(Element, OutElements);
				for (auto OutElement : OutElements)
				{
					for (auto Action : OutElement->Actions)
					{
						if (auto Preload= Cast<IPreloadable>(Action))
						{
							PreloadIds.Append(Preload->GetPreloadIds());
						}
					}
				}
			}
		}
	}
	PreloadsService->StartPreload(PreloadIds, FOnPreloadCompleted::CreateUObject(this,
		&UHistorySubsystem::OnPreloadsLoaded));
}

void UHistorySubsystem::OnPreloadsLoaded()
{
	for (auto Element : HistorySaveState->CurrentElements)
	{
		if (Element)
		{
			if (Element->bInitialized)
			{
				continue;
			}

			Element->Initialize();
		}
	}
}

void UHistorySubsystem::Inject()
{
	HistoryConfig = GetGameInstance()->GetSubsystem<UConfigsSubsystem>()->GetConfig<UHistoryConfig>();
	PreloadsService = GetGameInstance()->GetSubsystem<UPreloadSubsystem>();
}