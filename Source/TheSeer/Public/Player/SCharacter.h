// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SGameModeBase.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class ABaseChangeableActor;

DECLARE_DELEGATE_OneParam(FInputSwitchWorldModeSignature, WorldModes);

UCLASS()
class THESEER_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	virtual void BeginPlay() override;

private:
	bool bWantsToInteract = false;
	TArray<ABaseChangeableActor*> OverlapedActors;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void OnStartInteract();

	UFUNCTION()
	void SetWorldMode(WorldModes Mode);

	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
