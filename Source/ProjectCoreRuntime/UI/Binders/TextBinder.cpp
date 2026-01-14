// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "TextBinder.h"

#include "Components/TextBlock.h"

void UTextBinder::Bind(UTextBlock* TextBlock, const FText& Value)
{
	TextBlock->SetText(Value);
}
