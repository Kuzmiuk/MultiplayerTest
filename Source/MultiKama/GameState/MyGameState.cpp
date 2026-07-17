// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"
#include "Net/UnrealNetwork.h"
#include "MultiKama/PlayerState/MyPlayerState.h"
#include "MultiKama/PlayerController/MyPlayerController.h"

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyGameState, TopScoringPlayers);
	DOREPLIFETIME(AMyGameState, RedTeamScore);
	DOREPLIFETIME(AMyGameState, BlueTeamScore);
}

void AMyGameState::UpdateTopScore(class AMyPlayerState* ScoringPlayer)
{
	if (TopScoringPlayers.Num() == 0)
	{
		TopScoringPlayers.Add(ScoringPlayer);
		TopScore = ScoringPlayer->GetScore();
	}
	else if (ScoringPlayer->GetScore() == TopScore)
	{
		TopScoringPlayers.AddUnique(ScoringPlayer);
	}
	else if (ScoringPlayer->GetScore() > TopScore)
	{
		TopScoringPlayers.Empty();
		TopScoringPlayers.AddUnique(ScoringPlayer);
		TopScore = ScoringPlayer->GetScore();
	}
}

void AMyGameState::RedTeamScores()
{
	++RedTeamScore;
	AMyPlayerController* BPlayer = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (BPlayer)
	{
		BPlayer->SetHUDRedTeamScore(RedTeamScore);
	}
}

void AMyGameState::BlueTeamScores()
{
	++BlueTeamScore;
	AMyPlayerController* BPlayer = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (BPlayer)
	{
		BPlayer->SetHUDBlueTeamScore(BlueTeamScore);
	}
}

void AMyGameState::OnRep_RedTeamScore()
{
	AMyPlayerController* BPlayer = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (BPlayer)
	{
		BPlayer->SetHUDRedTeamScore(RedTeamScore);
	}
}

void AMyGameState::OnRep_BlueTeamScore()
{
	AMyPlayerController* BPlayer = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (BPlayer)
	{
		BPlayer->SetHUDBlueTeamScore(BlueTeamScore);
	}
}