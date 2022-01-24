// 10.8 Team. All rights reserved.

#include "UI/SMainUIWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "TimerManager.h"

void USMainUIWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeFrames();
	InitializeChangeDelegate();
	int CurrentScrolls = 0;
	int MaxLevelScrolls = 4;
	SubGoalText->SetText(FText::FromString(FString::Printf(TEXT("%i / %i"), CurrentScrolls, MaxLevelScrolls)));
}

void USMainUIWidget::OnChangeWorldMode(WorldModes GameMode)
{
	if (!GetWorld()) return;
	CurrentWorldFrame->SetVisibility(ESlateVisibility::Hidden);
	CurrentWorldFrame = *(WorldFrames.Find(GameMode));
	CurrentWorldFrame->SetVisibility(ESlateVisibility::Visible);
	CurrentTimeRecoveryPercent = 0.0f;
	GetWorld()->GetTimerManager().SetTimer(RecoveryTimer, this, &USMainUIWidget::RecoveryTimerUpdate, 0.1f, true);
}

void USMainUIWidget::RecoveryTimerUpdate()
{
	CurrentTimeRecoveryPercent += (0.1 / MaxTimeRecovery);
	if (FMath::IsNearlyEqual(CurrentTimeRecoveryPercent, MaxTimeRecovery))
	{
		GetWorld()->GetTimerManager().ClearTimer(RecoveryTimer);
	}
}

void USMainUIWidget::InitializeFrames()
{
	CurrentWorldFrame = FirstWorldFrame;
	SecondWorldFrame->SetVisibility(ESlateVisibility::Hidden);
	ThirdWorldFrame->SetVisibility(ESlateVisibility::Hidden);

	WorldFrames.Add(WorldModes::FirstWorld, FirstWorldFrame);
	WorldFrames.Add(WorldModes::SecondWorld, SecondWorldFrame);
	WorldFrames.Add(WorldModes::ThirdWorld, ThirdWorldFrame);
}

void USMainUIWidget::InitializeChangeDelegate()
{
	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->OnChangeWorldMode.AddUObject(this, &USMainUIWidget::OnChangeWorldMode);
}