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
	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	SubGoalText->SetText(FText::FromString(FString::Printf(TEXT("%i / %i"), GameMode->GetCurrentJournalPagesOnLevel(), GameMode->GetMaxJournalPagesOnLevel())));
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
	CurrentWorldFrame = SecondWorldFrame;
	FirstWorldFrame->SetVisibility(ESlateVisibility::Hidden);
	ThirdWorldFrame->SetVisibility(ESlateVisibility::Hidden);

	WorldFrames.Add(WorldModes::FirstWorld, FirstWorldFrame);
	WorldFrames.Add(WorldModes::SecondWorld, SecondWorldFrame);
	WorldFrames.Add(WorldModes::ThirdWorld, ThirdWorldFrame);
}

void USMainUIWidget::InitializeChangeDelegate()
{
	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->OnChangeWorldMode.AddDynamic(this, &USMainUIWidget::OnChangeWorldMode);
}

void USMainUIWidget::OnTakenPage()
{
	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	const auto CurrentPages = GameMode->GetCurrentJournalPagesOnLevel();
	const auto MaxPagesOnLevel = GameMode->GetMaxJournalPagesOnLevel();
	if (CurrentPages == MaxPagesOnLevel)
	{
		SubGoalText->SetText(FText::FromString(FString::Printf(TEXT("%i / %i - Completed"), CurrentPages, MaxPagesOnLevel)));
		return;
	}
	SubGoalText->SetText(FText::FromString(FString::Printf(TEXT("%i / %i"), CurrentPages, MaxPagesOnLevel)));
}