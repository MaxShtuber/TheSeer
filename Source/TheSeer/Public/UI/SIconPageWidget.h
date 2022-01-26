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
	UImage* IconPageImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* IconPageText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int PageNumber = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsLocked = true;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Images")
	TMap<int, UTexture2D*> LockImages;

private:
	UFUNCTION()
	void OpenPage();

};
