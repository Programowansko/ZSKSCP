// PyraSoft - Kacper Janas, Wiktor Ludwiniak, Jakub Mrugalski, Filip Nowicki
// Kacper Janas, Filip Nowicki(Voice chat)


#include "SCPCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../SCPZSK.h"
#include "Components/SCPHealthComponent.h"
#include "Components/SCPInventoryComponent.h"
#include "Components/SCPAmmoComponent.h"
#include "Net/UnrealNetwork.h"
#include "SCPItem.h"
#include "SCPWeapon.h"

// Sets default values
ASCPCharacter::ASCPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanJump = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);

	HealthComp = CreateDefaultSubobject<USCPHealthComponent>(TEXT("HealthComp"));

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	InventoryComp = CreateDefaultSubobject<USCPInventoryComponent>(TEXT("Inventory"));
	InventoryComp->Capacity = 8;

	RifleAmmoComp = CreateDefaultSubobject<USCPAmmoComponent>(TEXT("RifleAmmoComp"));

	VoiceCapture = FVoiceModule::Get().CreateVoiceCapture();

	VoiceCaptureAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("VoiceCaptureAudioComponent"));
	VoiceCaptureAudioComponent->SetupAttachment(RootComponent);
	VoiceCaptureAudioComponent->bAutoActivate = false;
	VoiceCaptureAudioComponent->bAlwaysPlay = false;
	VoiceCaptureAudioComponent->PitchMultiplier = 0.85f;
	VoiceCaptureAudioComponent->VolumeMultiplier = 5.f;

	VoiceCaptureSoundWaveProcedural = NewObject<USoundWaveProcedural>();
	VoiceCaptureSoundWaveProcedural->NumChannels = 1;
	VoiceCaptureSoundWaveProcedural->Duration = INDEFINITELY_LOOPING_DURATION;
	VoiceCaptureSoundWaveProcedural->SoundGroup = SOUNDGROUP_Voice;
	VoiceCaptureSoundWaveProcedural->bLooping = false;
	VoiceCaptureSoundWaveProcedural->bProcedural = true;
	VoiceCaptureSoundWaveProcedural->Pitch = 0.85f;
	VoiceCaptureSoundWaveProcedural->Volume = 5.f;
}

// Called when the game starts or when spawned
void ASCPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComp->OnHealthChanged.AddDynamic(this, &ASCPCharacter::OnHealthChanged);
	NormalMoveSpeed = GetCharacterMovement()->MaxWalkSpeed;

	if (Role == ROLE_Authority)
	{
		// Spawn a default weapon
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		CurrentWeapon = GetWorld()->SpawnActor<ASCPWeapon>(CurrentWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (CurrentWeapon)
		{
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSocketName);
			bWeaponEquipped = true;
		}
	}
}

void ASCPCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}


void ASCPCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void ASCPCharacter::BeginCrouch()
{
	Crouch();
}

void ASCPCharacter::EndCrouch()
{
	UnCrouch();
}

void ASCPCharacter::StartFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StartFire();
	}
}

void ASCPCharacter::StopFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
	}
}

void ASCPCharacter::BeginSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 700.0f;
}

void ASCPCharacter::BeginWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ASCPCharacter::ReturnToNormalMoveSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = NormalMoveSpeed;
}

void ASCPCharacter::Reload()
{
	if(CurrentWeapon)
	{
		if (CurrentWeaponClass == RifleWeaponClass) {
			if (RifleAmmoComp->Reload(CurrentWeapon->WeaponAmmoPerClip)) {
				CurrentWeapon->AmmoInClip = CurrentWeapon->WeaponAmmoPerClip;
			}
		}
	}
}

void ASCPCharacter::Heal(float HealAmount)
{
	HealthComp->Heal(HealAmount);
}

void ASCPCharacter::UseItem(USCPItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this); // Blueprint version
	}
}

void ASCPCharacter::EquipWeapon_Implementation(TSubclassOf<ASCPWeapon> ClassOfWeaponToEquip)
{
	if (Role == ROLE_Authority && ClassOfWeaponToEquip != CurrentWeaponClass)
	{
		// Spawn a weapon
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		CurrentWeapon = GetWorld()->SpawnActor<ASCPWeapon>(ClassOfWeaponToEquip, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

		if (CurrentWeapon)
		{
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSocketName);
			CurrentWeaponClass = ClassOfWeaponToEquip;
			bWeaponEquipped = true;
		}
	}
	else if(ClassOfWeaponToEquip == CurrentWeaponClass)
	{
		CurrentWeaponClass = nullptr;
		bWeaponEquipped = false;
		CurrentWeapon->Destroy();
	}
}

void ASCPCharacter::OnHealthChanged(USCPHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Health <= 0.0f && !bDied)
	{
		// Die!

		bDied = true;

		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		SetActorEnableCollision(true);

		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		DetachFromControllerPendingDestroy();

		// Lifetime of corpses
		//SetLifeSpan(10.0f);

		// Get name of the killer
		if (DamageCauser) 
		{
			FString KilledBy = DamageCauser->GetHumanReadableName();
			UE_LOG(LogTemp, Log, TEXT("Killed by: %s"), *KilledBy);
		}

		if (Role == ROLE_Authority)
			SetRagdoll();

		UCharacterMovementComponent* CharacterComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
		if (CharacterComp)
		{
			CharacterComp->StopMovementImmediately();
			CharacterComp->DisableMovement();
			CharacterComp->SetComponentTickEnabled(false);
		}
	}
}

void ASCPCharacter::SetRagdoll_Implementation()
{
	// Set ragdoll for dead player
	// @TODO: Replicate for everyone
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	GetMesh()->bBlendPhysics = true;
}

void ASCPCharacter::OnAmmoChanged(USCPAmmoComponent* OwningAmmoComp, float AmmoCount, float AmmoInClip)
{
	if(AmmoInClip <= 0.0f)
	{
		UE_LOG(LogTemp, Log, TEXT("No ammo in clip"));
	}
}

// Called every frame
void ASCPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCPCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ASCPCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ASCPCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASCPCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASCPCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &ASCPCharacter::BeginWalk);
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &ASCPCharacter::ReturnToNormalMoveSpeed);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASCPCharacter::BeginSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASCPCharacter::ReturnToNormalMoveSpeed);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCPCharacter::Jump);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ASCPCharacter::Reload);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASCPCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASCPCharacter::StopFire);
}

FVector ASCPCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
		return CameraComp->GetComponentLocation();

	return Super::GetPawnViewLocation();
}

void ASCPCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASCPCharacter, CurrentWeapon);
	DOREPLIFETIME(ASCPCharacter, bDied);
	DOREPLIFETIME(ASCPCharacter, bWeaponEquipped);
}

void ASCPCharacter::VoiceCaptureTick()
{
	VoiceCapture->Start();

	if (!VoiceCapture.IsValid())
		return;
	uint32 VoiceCaptureBytesAvailable = 0;
	EVoiceCaptureState::Type CaptureState = VoiceCapture->GetCaptureState(VoiceCaptureBytesAvailable);

	VoiceCaptureBuffer.Reset();
	PlayVoiceCaptureFlag = false;

	if (CaptureState == EVoiceCaptureState::Ok && VoiceCaptureBytesAvailable > 0)
	{
		int16_t VoiceCaptureSample;
		uint32 VoiceCaptureReadBytes;
		float VoiceCaptureTotalSquared = 0;

		VoiceCaptureBuffer.SetNumUninitialized(VoiceCaptureBytesAvailable);

		VoiceCapture->GetVoiceData(VoiceCaptureBuffer.GetData(), VoiceCaptureBytesAvailable, VoiceCaptureReadBytes);

		for (uint32 i = 0; i < (VoiceCaptureReadBytes / 2); i++)
		{
			VoiceCaptureSample = (VoiceCaptureBuffer[i * 2 + 1] << 8) | VoiceCaptureBuffer[i * 2];
			VoiceCaptureTotalSquared += ((float)VoiceCaptureSample * (float)VoiceCaptureSample);
		}

		float VoiceCaptureMeanSquare = (2 * (VoiceCaptureTotalSquared / VoiceCaptureBuffer.Num()));
		float VoiceCaptureRms = FMath::Sqrt(VoiceCaptureMeanSquare);
		float VoiceCaptureFinalVolume = ((VoiceCaptureRms / 32768.0) * 200.f);

		VoiceCaptureVolume = VoiceCaptureFinalVolume;

		VoiceCaptureSoundWaveProcedural->QueueAudio(VoiceCaptureBuffer.GetData(), VoiceCaptureReadBytes);
		VoiceCaptureAudioComponent->SetSound(VoiceCaptureSoundWaveProcedural);

		PlayVoiceCaptureFlag = true;
	}
}

void ASCPCharacter::PlayVoiceCapture()
{
	if (!VoiceCaptureAudioComponent->IsPlaying())
	{
		VoiceCaptureAudioComponent->FadeOut(0.3f, 0.f);
	}
	if (VoiceCaptureAudioComponent->IsPlaying())
		return;
	VoiceCaptureAudioComponent->Play();
}