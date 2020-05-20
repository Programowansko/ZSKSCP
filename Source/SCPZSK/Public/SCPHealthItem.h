// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCPItem.h"
#include "SCPHealthItem.generated.h"

/**
 * 
 */
UCLASS()
class SCPZSK_API USCPHealthItem : public USCPItem
{
	GENERATED_BODY()

public:

	/* Amount of Health to heal */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float HealAmount;

protected:
	
	virtual void Use(class ASCPCharacter* Character) override;
};
