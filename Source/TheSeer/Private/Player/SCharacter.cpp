// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/SCharacter.h"
#include "Camera/CameraComponent.h"
#include "Dev/BaseChangeableActor.h"
#include "Components/TextRenderComponent.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystem.h"

ASCharacter::ASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->bUsePawnControlRotation = true;
	ChangeWorldEffect = CreateDefaultSubobject<UNiagaraComponent>("ChangeWorldEffect");
	ChangeWorldEffect->SetupAttachment(CameraComponent);
}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	this->OnActorBeginOverlap.AddDynamic(this, &ASCharacter::OnBeginOverlap);
	this->OnActorEndOverlap.AddDynamic(this, &ASCharacter::OnEndOverlap);
	ChangeWorldEffect->AutoAttachScaleRule = EAttachmentRule::SnapToTarget;
	ChangeWorldEffect->Deactivate();
}

void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
	PlayerInputComponent->BindAction<FInputSwitchWorldModeSignature>("SetFirstWorld", IE_Pressed, this, &ASCharacter::SetWorldMode, WorldModes::FirstWorld);
	PlayerInputComponent->BindAction<FInputSwitchWorldModeSignature>("SetSecondWorld", IE_Pressed, this, &ASCharacter::SetWorldMode, WorldModes::SecondWorld);
	PlayerInputComponent->BindAction<FInputSwitchWorldModeSignature>("SetThirdWorld", IE_Pressed, this, &ASCharacter::SetWorldMode, WorldModes::ThirdWorld);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ASCharacter::OnStartInteract);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ASCharacter::PauseGame);
}

void ASCharacter::MoveForward(float Amount)
{
	if (FMath::IsNearlyZero(Amount)) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASCharacter::MoveRight(float Amount)
{
	if (FMath::IsNearlyZero(Amount)) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASCharacter::SetWorldMode(WorldModes Mode)
{
	if (!bCanSetWorld) return;
	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode || GameMode->GetWorldMode() == Mode) return;

	GameMode->SetWorldMode(Mode);
	ChangeWorldEffect->Activate();

	bCanSetWorld = false;
	GetWorld()->GetTimerManager().SetTimer(SetWorldTimerHandler, this, &ASCharacter::ChangeSetWorld, SetWorldTime);
}

void ASCharacter::ChangeSetWorld()
{
	bCanSetWorld = true;
	GetWorld()->GetTimerManager().ClearTimer(SetWorldTimerHandler);
}

void ASCharacter::OnStartInteract()
{
	if (OverlapedActors.Num() == 0) return;
	for (auto OverlapedActor : OverlapedActors)
	{
		if (!OverlapedActor) continue;
		OverlapedActor->SetMeshChangeable(OverlapedActor->GetMeshChangeable() ? false : true);
		auto ChangeTextCondition = (OverlapedActor->TextComponent->Text).ToString() == OverlapedActor->ActivateDescription.ToString();
		OverlapedActor->TextComponent->SetText(ChangeTextCondition ? OverlapedActor->DeactivateDescription : OverlapedActor->ActivateDescription);
	}
}

void ASCharacter::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const auto Actor = Cast<ABaseChangeableActor>(OtherActor);
	if (!Actor) return;

	Actor->TextComponent->SetVisibility(true);
	OverlapedActors.Emplace(Actor);
}

void ASCharacter::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const auto Actor = Cast<ABaseChangeableActor>(OtherActor);
	if (!Actor) return;
	Actor->TextComponent->SetVisibility(false);
	OverlapedActors.RemoveAt(OverlapedActors.Find(Actor));
}

void ASCharacter::PauseGame()
{
	const auto PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController) return;
	PlayerController->SetShowMouseCursor(true);
	PlayerController->SetPause(true);
	PlayerController->SetInputMode(FInputModeUIOnly::FInputModeUIOnly());
	
}