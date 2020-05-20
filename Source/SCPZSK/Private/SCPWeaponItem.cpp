// Fill out your copyright notice in the Description page of Project Settings.


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
