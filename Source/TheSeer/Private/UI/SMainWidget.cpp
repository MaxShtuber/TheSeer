// 10.8 Team. All rights reserved.

#include "UI/SMainWidget.h"
#include "SGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void USMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BackToMainMenuButton->OnClicked.AddDynamic(this, &USMainWidget::BackToMainMenu);
	
	SetVisibility(ESlateVisibility::Hidden);
}

void USMainWidget::OpenLevel()
{
	GetOwningPlayer()->SetPause(false);
	GetOwningPlayer()->SetShowMouseCursor(false);
	GetOwningPlayer()->SetInputMode(FInputModeGameOnly::FInputModeGameOnly());
	SetVisibility(ESlateVisibility::Hidden);
}

void USMainWidget::BackToMainMenu()
{
	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());

	GetOwningPlayer()->SetPause(false);
	GetOwningPlayer()->SetInputMode(FInputModeUIOnly::FInputModeUIOnly());
	UGameplayStatics::OpenLevel(GetWorld(), GameMode->GetMainMenuLevelName());
	SetVisibility(ESlateVisibility::Hidden);
}