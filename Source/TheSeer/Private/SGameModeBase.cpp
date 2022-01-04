// Fill out your copyright notice in the Description page of Project Settings.

#include "SGameModeBase.h"
#include "Player/SCharacter.h"
#include "Player/SPlayerController.h"

ASGameModeBase::ASGameModeBase()
{
	DefaultPawnClass = ASCharacter::StaticClass();
	PlayerControllerClass = ASPlayerController::StaticClass();
	SetWorldMode(WorldModes::FirstWorld);
}

void ASGameModeBase::SetWorldMode(const WorldModes& Mode)
{
	if (Mode == CurrentWorldMode) return;

	CurrentWorldMode = Mode;
	OnChangeWorldMode.Broadcast(CurrentWorldMode);
}