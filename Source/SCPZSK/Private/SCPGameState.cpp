// Fill out your copyright notice in the Description page of Project Settings.


#include "SCPGameState.h"
#include "Net/UnrealNetwork.h"

void ASCPGameState::OnRep_WaveState(EWaveState OldState)
{
	WaveStateChanged(WaveState, OldState);
}

void ASCPGameState::SetWaveState(EWaveState NewState)
{
	if (Role == ROLE_Authority)
	{
		EWaveState OldState = WaveState;

		WaveState = NewState;
		OnRep_WaveState(OldState);
	}
}

void ASCPGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASCPGameState, WaveState);
}