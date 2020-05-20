// Fill out your copyright notice in the Description page of Project Settings.


#include "SCPTesla.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "SCPCharacter.h"
#include "Components/SCPHealthComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASCPTesla::ASCPTesla()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetCollisionProfileName(TEXT("Trigger"));
	OverlapComp->SetBoxExtent(FVector(300.0f, 300.0f, 350.0f));
	RootComponent = OverlapComp;

	OverlapComp->SetHiddenInGame(false);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ASCPTesla::HandleOverlap);
	OverlapComp->OnComponentEndOverlap.AddDynamic(this, &ASCPTesla::OnOverlapEnd);

	DamageZone = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageZone"));
	DamageZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DamageZone->SetCollisionResponseToAllChannels(ECR_Ignore);
	DamageZone->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	DamageZone->SetBoxExtent(FVector(20.0f, 300.0f, 400.0f));
	DamageZone->SetupAttachment(RootComponent);

	DamageZone->OnComponentBeginOverlap.AddDynamic(this, &ASCPTesla::HandleOverlapAndDamagePlayer);

	RateOfFire = 18;
	ShotDuration = 1.0f;

	SetReplicates(true);

	NetUpdateFrequency = 66.0f;
	MinNetUpdateFrequency = 33.0f;
}

void ASCPTesla::BeginPlay()
{
	Super::BeginPlay();

	TimeBetweenShots = 60 / RateOfFire;
}


void ASCPTesla::StartFire()
{
	float FirstDelay = FMath::Max(LastFiredTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.5f);

	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &ASCPTesla::Fire, TimeBetweenShots, true, FirstDelay);

}

void ASCPTesla::Fire()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		ServerFire();
	}

	bIsDealingDamage = true;
	DamageZone->SetHiddenInGame(false);
	if(HitEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation());
	}

	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
	}

	LastFiredTime = GetWorld()->TimeSeconds;

	UE_LOG(LogTemp, Log, TEXT("Started dealing damage"));
	
	DamageZone->GetOverlappingActors(OverlappingActors, PlayerClass);
	if (OverlappingActors.Num() > 0) {
		for (int i = 0; i < OverlappingActors.Num(); i++) {
			DealDamage(OverlappingActors[i]);
		}
	}

	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenDamage, this, &ASCPTesla::ToggleDealingDamage, ShotDuration, false);
}

void ASCPTesla::ToggleDealingDamage() 
{
	bIsDealingDamage = false;
	UE_LOG(LogTemp, Log, TEXT("Stopped dealing damage"));
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenDamage);
}

void ASCPTesla::StopFire()
{
	bIsDealingDamage = false;
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
}

// WTF IS THIS but it works so its fine I guess

void ASCPTesla::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	StartFire();
}


void ASCPTesla::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		StopFire();
		UE_LOG(LogTemp, Log, TEXT("Stepped outside zone"));
	}
}

void ASCPTesla::HandleOverlapAndDamagePlayer(UPrimitiveComponent* OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(bIsDealingDamage)
	{
		DealDamage(OtherActor);
	}
}

void ASCPTesla::DealDamage(AActor* PlayerPawn)
{
	UGameplayStatics::ApplyDamage(PlayerPawn, 500.0f, nullptr, this, nullptr);
	UE_LOG(LogTemp, Log, TEXT("Dealing damage"));
}

void ASCPTesla::ServerFire_Implementation()
{
	Fire();
}

bool ASCPTesla::ServerFire_Validate()
{
	return true;
}

