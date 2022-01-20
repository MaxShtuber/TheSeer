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

	UFUNCTION()
	virtual void OpenLevel();

	UFUNCTION()
	virtual void ExitLevel();

	virtual void NativeOnInitialized() override;

};
