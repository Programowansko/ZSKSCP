// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Jakub Mrugalski

#include "..\Public\SCPElevator.h"
#include "Components\BoxComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ASCPElevator::ASCPElevator()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    TeleportZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TeleportZone"));
    TeleportZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TeleportZone->SetCollisionResponseToAllChannels(ECR_Ignore);
    TeleportZone->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    TeleportZone->SetBoxExtent(FVector(175.0f, 175.0f, 175.0f));
    TeleportZone->SetHiddenInGame(false);
    RootComponent = TeleportZone;

    ElevatorDelay = 5.0f;

    SetReplicates(true);



}

// Called when the game starts or when spawned
void ASCPElevator::BeginPlay()
{
    Super::BeginPlay();

}

void ASCPElevator::InteractWithElevator()
{
    Cast<ASCPElevator>(TargetElevator)->bIsOpened = false;
    bIsOpened = false;
    // @TODO: Add close animation

    FTimerHandle TimerHandle_Elevator;
    GetWorldTimerManager().SetTimer(TimerHandle_Elevator, this, &ASCPElevator::TeleportPlayers, ElevatorDelay);
    Cast<ASCPElevator>(TargetElevator)->bIsOpened = true;

}

void ASCPElevator::TeleportPlayers()
{
    TArray<AActor*> OverlappingActors;
    TeleportZone->GetOverlappingActors(OverlappingActors);
    if (OverlappingActors.Num() > 0) {
        for (int i = 0; i < OverlappingActors.Num(); i++) {
            // @TODO: Fix relative rotation
            APlayerController* PC = UGameplayStatics::GetPlayerController(OverlappingActors[i], 0);
            PC->DisableInput(PC);
            RelativePosition = GetActorLocation() - OverlappingActors[i]->GetActorLocation();
            RelativeRotation = GetActorRotation() - PC->GetControlRotation();
            FRotator NewRotation = FRotator(0.f, 0.f, 10.f);
            FQuat QuatRotation = FQuat(NewRotation);
            OverlappingActors[i]->TeleportTo(TargetElevator->GetActorLocation() - RelativePosition, RelativeRotation);

            PC->EnableInput(PC);
        }
    }
}

// Called every frame
void ASCPElevator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}