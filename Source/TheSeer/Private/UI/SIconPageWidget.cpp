// 10.8 Team. All rights reserved.

#include "UI/SIconPageWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"

void USIconPageWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	IconPageButton->OnClicked.AddDynamic(this, &USIconPageWidget::OpenPage);
	IconPageImage->SetBrushFromTexture(*LockImages.Find(0));
}

void USIconPageWidget::OpenPage()
{
	if (IsLocked) return;
	OnOpenIconPage.Broadcast(PageNumber);
}