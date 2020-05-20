// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCPCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USCPHealthComponent;
class USCPItem;
class USCPInventoryComponent;
class USCPAmmoComponent;
class ASCPWeapon;

UCLASS()
class SCPZSK_API ASCPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCPCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USCPHealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USCPInventoryComponent* InventoryComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USCPAmmoComponent* RifleAmmoComp;

	// Movement
	void MoveForward(float Value);
	void MoveRight(float Value);

	// Crouching
	void BeginCrouch();
	void EndCrouch();

	// Sprinting/Walking
	void BeginSprint();
	void BeginWalk();

	void ReturnToNormalMoveSpeed();
	float NormalMoveSpeed;

	UFUNCTION()
	void OnHealthChanged(USCPHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(Reliable, Server)
	void SetRagdoll();

	UFUNCTION()
	void OnAmmoChanged(USCPAmmoComponent* OwningAmmoComp, float AmmoCount, float AmmoInClip);

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
	bool bDied;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Player")
	bool bWeaponEquipped;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Player")
	ASCPWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<ASCPWeapon> CurrentWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<ASCPWeapon> RifleWeaponClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	FName WeaponAttachSocketName;

	void StartFire();
	void StopFire();

public:

	UFUNCTION()
	void Reload();

	UFUNCTION()
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(USCPItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Items")
	void EquipWeapon(TSubclassOf<ASCPWeapon> ClassOfWeaponToEquip);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

};
