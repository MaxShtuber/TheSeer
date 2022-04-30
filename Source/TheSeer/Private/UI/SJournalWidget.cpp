// 10.8 Team. All rights reserved.

#include "UI/SJournalWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "SGameModeBase.h"
#include "Player/SCharacter.h"
#include "Engine/World.h"
#include "UI/SIconPageWidget.h"

void USJournalWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeDelegates();
	SetVisibility(ESlateVisibility::Hidden);
}

void USJournalWidget::OnExit()
{
	if (IsValid(CloseSound))
	{
		PlaySound(CloseSound);
	}
	GetOwningPlayer()->SetPause(false);
	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer()->SetInputMode(FInputModeGameOnly::FInputModeGameOnly());
	GetOwningPlayer()->SetShowMouseCursor(false);
}

void USJournalWidget::OnOpenJournal()
{
	if (IsValid(OpenSound))
	{
		PlaySound(OpenSound);
	}
	SetVisibility(ESlateVisibility::Visible);
}

void USJournalWidget::InitializeDelegates()
{
	ExitButton->OnClicked.AddDynamic(this, &USJournalWidget::OnExit);

	const auto Character = Cast<ASCharacter>(GetOwningPlayerPawn());
	if (Character)
	{
		Character->OnJournalOpen.AddUObject(this, &USJournalWidget::OnOpenJournal);
		Character->OnJournalSetPage.AddUObject(this, &USJournalWidget::OpenPage);
	}
	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	const auto NumberOfPages = GameMode->GetMaxJournalPages();
	for (auto i = 0; i < NumberOfPages; i++)
	{
		auto OnePage = CreateWidget<USIconPageWidget>(this, IconPage);
		OnePage->PageNumber = i;
		OnePage->IconPageText->SetText(FText::FromString(FString::Printf(TEXT("%i"), i+1)));
		OnePage->OnOpenIconPage.AddUObject(this, &USJournalWidget::OpenPage);
		GridPages->AddChild(OnePage);
	}

}

void USJournalWidget::OpenPage(int PageNumber)
{
	if (PageSounds.Num() > 0)
	{
		PlaySound(PageSounds[FMath::RandRange(0, PageSounds.Num() - 1)]);
	}
	CoreImage->SetBrushFromTexture(*PageImages.Find(PageNumber));
}