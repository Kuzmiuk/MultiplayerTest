// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiKamaGameMode.h"
#include "MultiKama/Character/MyCharacter.h"
#include "MultiKama/PlayerController/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "MultiKama/PlayerState/MyPlayerState.h"
#include <MultiKama/GameState/MyGameState.h>

namespace MatchState
{
	const FName Cooldown = FName("Cooldown");
}

AMultiKamaGameMode::AMultiKamaGameMode()
{
	bDelayedStart = true;
}

void AMultiKamaGameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelStartingTime = GetWorld()->GetTimeSeconds();
}

void AMultiKamaGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MatchState == MatchState::WaitingToStart)
	{
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			StartMatch();
		}
	}
	else if (MatchState == MatchState::InProgress)
	{
		CountdownTime = WarmupTime + MatchTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			SetMatchState(MatchState::Cooldown);
		}
	}
	else if (MatchState == MatchState::Cooldown)
	{
		CountdownTime = CooldownTime + WarmupTime + MatchTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			RestartGame();
		}
	}
}

void AMultiKamaGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AMyPlayerController* MultiKamaPlayer = Cast<AMyPlayerController>(*It);
		if (MultiKamaPlayer)
		{
			MultiKamaPlayer->OnMatchStateSet(MatchState, bTeamsMatch);
		}
	}
}

float AMultiKamaGameMode::CalculateDamage(AController* Attacker, AController* Victim, float BaseDamage)
{
	return BaseDamage;
}

void AMultiKamaGameMode::PlayerEliminated(class AMyCharacter* ElimmedCharacter,class AMyPlayerController* VictimController,class AMyPlayerController* AttackerController)
{
	if (AttackerController == nullptr || AttackerController->PlayerState == nullptr) return;
	if (VictimController == nullptr || VictimController->PlayerState == nullptr) return;
	AMyPlayerState* AttackerPlayerState = AttackerController ? Cast<AMyPlayerState>(AttackerController->PlayerState) : nullptr;
	AMyPlayerState* VictimPlayerState =	VictimController ? Cast<AMyPlayerState>(VictimController->PlayerState) : nullptr;

	AMyGameState* CurrentGameState = GetGameState<AMyGameState>();

	if (AttackerPlayerState && AttackerPlayerState != VictimPlayerState && CurrentGameState)
	{
		TArray<AMyPlayerState*> PlayersCurrentlyInTheLead;
		for (auto LeadPlayer : CurrentGameState->TopScoringPlayers)
		{
			PlayersCurrentlyInTheLead.Add(LeadPlayer);
		}

		AttackerPlayerState->AddToScore(1.f);
		CurrentGameState->UpdateTopScore(AttackerPlayerState);
		if (CurrentGameState->TopScoringPlayers.Contains(AttackerPlayerState))
		{
			AMyCharacter* Leader = Cast<AMyCharacter>(AttackerPlayerState->GetPawn());
			if (Leader)
			{
				Leader->MulticastGainedTheLead();
			}
		}

		for (int32 i = 0; i < PlayersCurrentlyInTheLead.Num(); i++)
		{
			if (!CurrentGameState->TopScoringPlayers.Contains(PlayersCurrentlyInTheLead[i]))
			{
				AMyCharacter* Loser = Cast<AMyCharacter>(PlayersCurrentlyInTheLead[i]->GetPawn());
				if (Loser)
				{
					Loser->MulticastLostTheLead();
				}
			}
		}
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->AddToDefeats(1);
	}

	if (ElimmedCharacter)
	{
		ElimmedCharacter->Elim(false);
	}

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AMyPlayerController* PlayerController = Cast<AMyPlayerController>(*It);
		if (PlayerController && AttackerPlayerState && VictimPlayerState)
		{
			PlayerController->BroadcastElim(AttackerPlayerState, VictimPlayerState);
		}
	}
}

void AMultiKamaGameMode::RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController)
{
	if (ElimmedCharacter)
	{
		ElimmedCharacter->Reset();
		ElimmedCharacter->Destroy();
	}
	if (ElimmedController)
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(ElimmedController, PlayerStarts[Selection]);
	}
}

void AMultiKamaGameMode::PlayerLeftGame(AMyPlayerState* PlayerLeaving)
{
	if (PlayerLeaving == nullptr) return;

	AMyGameState* MyGameState = GetGameState<AMyGameState>();

	if (MyGameState && MyGameState->TopScoringPlayers.Contains(PlayerLeaving))
	{
		MyGameState->TopScoringPlayers.Remove(PlayerLeaving);
	}

	AMyCharacter* CharacterLeaving = Cast<AMyCharacter>(PlayerLeaving->GetPawn());
	if (CharacterLeaving)
	{
		CharacterLeaving->Elim(true);
	}
}