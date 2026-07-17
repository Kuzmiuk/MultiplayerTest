#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MultiKamaGameMode.generated.h"

namespace MatchState
{
	extern MULTIKAMA_API const FName Cooldown;
}

/**
 *
 */
UCLASS()
class MULTIKAMA_API AMultiKamaGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AMultiKamaGameMode();
	virtual void Tick(float DeltaTime) override;
	virtual void PlayerEliminated(class AMyCharacter* ElimmedCharacter, class AMyPlayerController* VictimController,class AMyPlayerController* AttackerController);
	virtual void RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController);
	void PlayerLeftGame(class AMyPlayerState* PlayerLeaving);
	virtual float CalculateDamage(AController* Attacker, AController* Victim, float BaseDamage);
	UPROPERTY(EditDefaultsOnly)
	float WarmupTime = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float MatchTime = 120.f;

	UPROPERTY(EditDefaultsOnly)
	float CooldownTime = 10.f;

	float LevelStartingTime = 0.f;

	bool bTeamsMatch = false;
protected:
	virtual void BeginPlay() override;	
	virtual void OnMatchStateSet() override;

private:
	float CountdownTime = 0.f;
public:
	FORCEINLINE float GetCountdownTime() const { return CountdownTime; }
};