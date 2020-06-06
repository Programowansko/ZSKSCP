// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SCPItem.generated.h"

class UWorld;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class SCPZSK_API USCPItem : public UObject
{
	GENERATED_BODY()
	
public:

	USCPItem();

	virtual UWorld* GetWorld() const { return World; };

	UPROPERTY(Transient)
	UWorld* World;

	/* Text for using the item (Equip, Eat, Use) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText UseActionText;

	/* Mesh to display for this item pickup */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UStaticMesh* PickupMesh;

	/* Thumbnail for the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UTexture2D* Thumbnail;

	/* Name of the item in the inventory */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemDisplayName;

	/* Optional description for the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (Multiline = true))
	FText ItemDescr;

	/* Weight of the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float Weight;

	UPROPERTY()
	class USCPInventoryComponent* OwningInventory;

	virtual void Use(class ASCPCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class ASCPCharacter* Character);
};
