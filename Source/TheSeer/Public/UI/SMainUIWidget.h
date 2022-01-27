// 10.8 Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGameModeBase.h"
#include "SMainUIWidget.generated.h"

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class THESEER_API USMainUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Widgets")
	float GetCurrentTimeRecoveryPercent() const { return CurrentTimeRecoveryPercent; };

	void OnTakenPage();

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* FirstWorldFrame;

	UPROPERTY(meta = (BindWidget))
	UImage* SecondWorldFrame;

	UPROPERTY(meta = (BindWidget))
	UImage* ThirdWorldFrame;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SubGoalText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ProgressBar")
	float MaxTimeRecovery = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ProgressBar")
	float CurrentTimeRecoveryPercent = 1.0f;

	virtual void NativeOnInitialized() override;
private:
	UImage* CurrentWorldFrame = FirstWorldFrame;
	TMap<WorldModes, UImage*> WorldFrames;
	FTimerHandle RecoveryTimer;

	UFUNCTION()
	void OnChangeWorldMode(WorldModes GameMode);

	void RecoveryTimerUpdate();
	void InitializeFrames();
	void InitializeChangeDelegate();
};
