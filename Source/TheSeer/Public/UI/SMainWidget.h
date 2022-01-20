// 10.8 Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/SMainMenuWidget.h"
#include "SMainWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class THESEER_API USMainWidget : public USMainMenuWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* BackToMainMenuButton;

	virtual void OpenLevel() override;
	virtual void NativeOnInitialized() override;
private:
	UFUNCTION()
	void BackToMainMenu();

};
