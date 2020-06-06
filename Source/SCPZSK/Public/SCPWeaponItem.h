// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas

#pragma once

#include "CoreMinimal.h"
#include "SCPItem.h"
#include "SCPWeaponItem.generated.h"


class ASCPWeapon;

/**
 * 
 */
UCLASS()
class SCPZSK_API USCPWeaponItem : public USCPItem
{
	GENERATED_BODY()

public:

	/* Class of weapon to equip */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<ASCPWeapon> WeaponClass;

protected:

	virtual void Use(class ASCPCharacter* Character) override;
};
