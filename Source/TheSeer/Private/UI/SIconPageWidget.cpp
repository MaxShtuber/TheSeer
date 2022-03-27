// 10.8 Team. All rights reserved.

#include "UI/SIconPageWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"

void USIconPageWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	IconPageButton->OnClicked.AddDynamic(this, &USIconPageWidget::OpenPage);
	IconPageButton->SetColorAndOpacity(FLinearColor::Black);
}

void USIconPageWidget::OpenPage()
{
	if (IsLocked) return;
	OnOpenIconPage.Broadcast(PageNumber);
}

void USIconPageWidget::OnTakenPage(int Number)
{
	if (Number != PageNumber) return;
	IsLocked = false;
	IconPageButton->SetColorAndOpacity(FLinearColor::White);
	IconPageButton->SetRenderOpacity(1.0f);
}