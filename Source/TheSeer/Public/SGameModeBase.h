// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeWorldModeSignature, WorldModes);

UENUM()
enum class WorldModes : uint8
{
	FirstWorld = 0,
	SecondWorld,
	ThirdWorld
};

/**
 * 
 */
UCLASS()
class THESEER_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASGameModeBase();

	FOnChangeWorldModeSignature OnChangeWorldMode;

	void SetWorldMode(const WorldModes& Mode);
	WorldModes GetWorldMode() const { return CurrentWorldMode; };
	FName GetMainLevelName() const { return MainLevel; };

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Levels")
	FName MainLevel = "MainLevel";

private:
	WorldModes CurrentWorldMode = WorldModes::FirstWorld;

};
