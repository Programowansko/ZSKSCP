// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas


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
