// 10.8 Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SMainMenuWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class THESEER_API USMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OpenLevel();

	UFUNCTION()
	void ExitLevel();
};
