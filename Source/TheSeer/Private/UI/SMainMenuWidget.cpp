// 10.8 Team. All rights reserved.

#include "UI/SMainMenuWidget.h"
#include "SGameModeBase.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void USMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	StartButton->OnClicked.AddDynamic(this, &USMainMenuWidget::OpenLevel);
	ExitButton->OnClicked.AddDynamic(this, &USMainMenuWidget::ExitLevel);
}

void USMainMenuWidget::OpenLevel()
{
	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());

	UGameplayStatics::OpenLevel(GetWorld(), GameMode->GetMainLevelName());
	GetOwningPlayer()->SetInputMode(FInputModeGameOnly::FInputModeGameOnly());
	GetOwningPlayer()->SetShowMouseCursor(false);
}

void USMainMenuWidget::ExitLevel()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}