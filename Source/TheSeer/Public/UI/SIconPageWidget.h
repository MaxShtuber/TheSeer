// 10.8 Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SIconPageWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;
class UTexture2D;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnOpenIconPageSignature, int);

/**
 * 
 */
UCLASS()
class THESEER_API USIconPageWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FOnOpenIconPageSignature OnOpenIconPage;

	UPROPERTY(meta = (BindWidget))
	UButton* IconPageButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* IconPageText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int PageNumber = 0;

	UFUNCTION(BlueprintCallable)
	void OnTakenPage(int Number);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsLocked = true;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OpenPage();

};
