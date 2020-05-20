// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SCPAmmoComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAmmoChangedSignature, USCPAmmoComponent*, AmmoComp, float, AmmoCount, float, AmmoInClip);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCPZSK_API USCPAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USCPAmmoComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing = OnRep_Ammo, EditDefaultsOnly, BlueprintReadOnly, Category = "AmmoComponent")
	float AmmoCount;

	UPROPERTY(ReplicatedUsing = OnRep_Ammo, EditDefaultsOnly, BlueprintReadOnly, Category = "AmmoComponent")
	float AmmoInClip;

	UFUNCTION()
	void OnRep_Ammo();

	UFUNCTION()
	void HandleAmmoChanges(AActor* ChangedAmmoActor, float OwnerAmmoCount, float OwnerAmmoInClip, float MaxAmmo);

public:	

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAmmoChangedSignature OnAmmoChanged;

	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
	bool Reload(float AmmoPerClip);

	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
	void AddAmmo(float AmmoToAdd, float MaxAmmo);
};
