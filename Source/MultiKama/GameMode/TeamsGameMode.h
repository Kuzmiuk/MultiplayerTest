// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiKamaGameMode.h"
#include "TeamsGameMode.generated.h"

/**
 *
 */
UCLASS()
class MULTIKAMA_API ATeamsGameMode : public AMultiKamaGameMode
{
	GENERATED_BODY()
public:
	ATeamsGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual float CalculateDamage(AController* Attacker, AController* Victim, float BaseDamage) override;
	virtual void PlayerEliminated(class AMyCharacter* ElimmedCharacter, class AMyPlayerController* VictimController, AMyPlayerController* AttackerController) override;
protected:
	virtual void HandleMatchHasStarted() override;
};