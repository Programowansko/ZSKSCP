// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas


#include "SCPWeaponItem.h"
#include "Components/SCPInventoryComponent.h"
#include "SCPCharacter.h"

void USCPWeaponItem::Use(class ASCPCharacter* Character)
{
	if (Character)
	{
		Character->EquipWeapon(WeaponClass);
	}
}
