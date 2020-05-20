// Fill out your copyright notice in the Description page of Project Settings.


#include "SCPItem.h"

USCPItem::USCPItem()
{
	Weight = 1.0f;
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}

void USCPItem::Use(class ASCPCharacter* Character)
{

}
