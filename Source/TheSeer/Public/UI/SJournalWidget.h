// 10.8 Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SJournalWidget.generated.h"

class UButton;
class UScrollBox;
class UImage;
class USIconPageWidget;
class UTexture2D;

/**
 * 
 */
UCLASS()
class THESEER_API USJournalWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* OpenSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* CloseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USoundBase*> PageSounds;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* GridPages;

	UPROPERTY(meta = (BindWidget))
	UImage* CoreImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USIconPageWidget> IconPage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, UTexture2D*> PageImages;

	virtual void NativeOnInitialized() override;
private:
	UFUNCTION()
	void OnExit();

	UFUNCTION()
	void OnOpenJournal();

	UFUNCTION()
	void OpenPage(int PageNumber);

	void InitializeDelegates();
};
