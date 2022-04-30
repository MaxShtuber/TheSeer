// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class WorldModes : uint8
{
	None = 0,
	FirstWorld,
	SecondWorld,
	ThirdWorld
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeWorldModeSignature, WorldModes, mode);
DECLARE_EVENT_OneParam(FOnChangeWorldModeSignature, FMode, WorldModes)

/**
 * 
 */
UCLASS()
class THESEER_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASGameModeBase();
	
	UPROPERTY(BlueprintAssignable)
	FOnChangeWorldModeSignature OnChangeWorldMode;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnChangeWorldModeSignature OnRuneTake;

	void SetWorldMode(const WorldModes& Mode);
	void OnTakenPage(int Number);
	void AddTakenRune(WorldModes& Mode);
	
	bool CanWorldChange(WorldModes& Mode);

	UFUNCTION(BlueprintCallable)
	WorldModes GetWorldMode() const { return CurrentWorldMode; };
	
	FName GetMainLevelName() const { return MainLevel; };
	FName GetMainMenuLevelName() const { return MainMenuLevel; };
	int32 GetMaxJournalPages() const { return MaxJournalPages; };
	int32 GetMaxJournalPagesOnLevel() const { return MaxJournalPagesOnLevel; };
	int32 GetCurrentJournalPagesOnLevel() const { return CurrentJournalPagesOnLevel; };

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Levels")
	FName MainLevel = "MainLevel";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Levels")
	FName MainMenuLevel = "MainMenuLevel";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Journal")
	int32 MaxJournalPages = 16;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Journal")
	int32 MaxJournalPagesOnLevel = 4;

private:
	WorldModes CurrentWorldMode = WorldModes::FirstWorld;
	int32 CurrentJournalPagesOnLevel = 0;
	TArray<WorldModes> CurrentTakenRunes;

	bool FindInArray(WorldModes& Mode);
};
