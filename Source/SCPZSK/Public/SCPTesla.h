// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCPTesla.generated.h"

class UBoxComponent;
class UParticleSystem;
class UParticleSystemComponent;
class USCPHealthComponent;

UCLASS()
class SCPZSK_API ASCPTesla : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASCPTesla();

protected:

	virtual void BeginPlay();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* DamageZone;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void HandleOverlapAndDamagePlayer(UPrimitiveComponent* OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void DealDamage(AActor* PlayerPawn);

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	UParticleSystem* HitEffect;

	UPROPERTY(EditAnywhere, Category = "Damage")
	bool bIsDealingDamage;

	virtual void Fire();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();

	FTimerHandle TimerHandle_TimeBetweenShots;
	FTimerHandle TimerHandle_TimeBetweenDamage;

	UFUNCTION()
	void ToggleDealingDamage();

	float LastFiredTime;

	/* RPM - Shots per minute fired by tesla */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float RateOfFire;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float ShotDuration;

	// Derived from RateOfFire
	float TimeBetweenShots;

	TArray<AActor*> OverlappingActors;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<AActor> PlayerClass;

public:

	void StartFire();

	void StopFire();
};
