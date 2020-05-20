// Fill out your copyright notice in the Description page of Project Settings.


#include "SCPHealthItem.h"
#include "Components/SCPInventoryComponent.h"
#include "SCPCharacter.h"

void USCPHealthItem::Use(class ASCPCharacter* Character)
{
	if(Character)
	{
		Character->Heal(HealAmount);

		if(OwningInventory)
		{
			OwningInventory->RemoveItem(this);
		}
	}
}
