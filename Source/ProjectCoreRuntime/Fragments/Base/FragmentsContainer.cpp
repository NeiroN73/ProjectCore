// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "FragmentsContainer.h"

TArray<UFragment*> UFragmentsContainer::GetFragments()
{
	TArray<UFragment*> Result;
	for (auto& [Class, Fragment] : FragmentsByType)
	{
		Result.Add(Fragment);
	}
	return Result;
}
