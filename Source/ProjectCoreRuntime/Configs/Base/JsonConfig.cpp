// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "JsonConfig.h"

#include "UObject/ObjectSaveContext.h"

#if WITH_EDITOR
void UJsonConfig::PostLoad()
{
	Super::PostLoad();

	ReadJson();
}

void UJsonConfig::PreSave(FObjectPreSaveContext SaveContext)
{
	Super::PreSave(SaveContext);

	WriteJson();
}
#endif
