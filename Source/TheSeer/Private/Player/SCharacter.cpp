// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Dev/BaseChangeableActor.h"
#include "Dev/BasePageActor.h"
#include "Dev/QuestPlaceActor.h"
#include "Dev/BaseRuneActor.h"
#include "Components/TextRenderComponent.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

ASCharacter::ASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = true;
	ChangeWorldEffect = CreateDefaultSubobject<UNiagaraComponent>("ChangeWorldEffect");
	ChangeWorldEffect->SetupAttachment(CameraComponent);
}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	this->OnActorBeginOverlap.AddDynamic(this, &ASCharacter::OnBeginOverlap);
	this->OnActorEndOverlap.AddDynamic(this, &ASCharacter::OnEndOverlap);
	ChangeWorldEffect->AutoAttachScaleRule = EAttachmentRule::KeepRelative;
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
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASCharacter::StopSprint);
	PlayerInputComponent->BindAction<FInputSwitchWorldModeSignature>("SetFirstWorld", IE_Pressed, this, &ASCharacter::SetWorldMode, WorldModes::FirstWorld);
	PlayerInputComponent->BindAction<FInputSwitchWorldModeSignature>("SetSecondWorld", IE_Pressed, this, &ASCharacter::SetWorldMode, WorldModes::SecondWorld);
	PlayerInputComponent->BindAction<FInputSwitchWorldModeSignature>("SetThirdWorld", IE_Pressed, this, &ASCharacter::SetWorldMode, WorldModes::ThirdWorld);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ASCharacter::OnStartInteract);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ASCharacter::PauseGame);
	PlayerInputComponent->BindAction("TakeObject", IE_Pressed, this, &ASCharacter::TakeObject);
	PlayerInputComponent->BindAction("DropObject", IE_Pressed, this, &ASCharacter::DropObject);
	PlayerInputComponent->BindAction("OpenJournal", IE_Pressed, this, &ASCharacter::OnOpenJournal);
}

void ASCharacter::EnableChangeWorld()
{
	bRestrictSetWorld = false;
}

void ASCharacter::DisableChangeWorld()
{
	bRestrictSetWorld = true;
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
	if (!bCanSetWorld || bRestrictSetWorld)
	{
		UnableToChangeWorld.Broadcast();
		return;
	}
	const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode || GameMode->GetWorldMode() == Mode) return;
	if (!GameMode->CanWorldChange(Mode)) return;
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
	FVector Location;
	FRotator Rotation;
	Controller->GetPlayerViewPoint(Location, Rotation);

	const auto StartPoint = Location;
	const auto Direction = Rotation.Vector();
	const auto EndPoint = StartPoint + RangeOfTakenObject * Direction;
	DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 2.0f, 0, 3.0f);
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility, CollisionParams);

	if (!HitResult.bBlockingHit) return;

	const auto HittedPageObject = Cast<ABasePageActor>(HitResult.GetActor());
	if (HittedPageObject)
	{
		HittedPageObject->OnStartInteract();
		OnOpenJournal();
		OnJournalSetPage.Broadcast(HittedPageObject->GetPageNumber());
		return;
	}

	const auto HittedPlaceObject = Cast<AQuestPlaceActor>(HitResult.GetActor());
	if (HittedPlaceObject && HittedPlaceObject->CanInteract() && CurrentTakenActor && CurrentTakenActor->TagItem == HittedPlaceObject->TagItem)
	{
		const auto DetachmentRules = FDetachmentTransformRules::KeepWorldTransform;
		CurrentTakenActor->DetachFromActor(DetachmentRules);
		CurrentTakenActor->SetMeshChangeable(true);
		CurrentTakenActor->EnableCurrentMeshPhysics();

		CurrentTakenActor->Destroy();
		CurrentTakenActor = nullptr;
		HittedPlaceObject->OnStartInteract();
		return;
	}

	const auto HittedRuneObject = Cast<ABaseRuneActor>(HitResult.GetActor());
	if (HittedRuneObject)
	{
		HittedRuneObject->OnStartInteract();
		return;
	}

}

void ASCharacter::StartSprint()
{
	StaticCast<UCharacterMovementComponent*>(GetMovementComponent())->MaxWalkSpeed = SprintSpeed;
}

void ASCharacter::StopSprint()
{
	StaticCast<UCharacterMovementComponent*>(GetMovementComponent())->MaxWalkSpeed = WalkSpeed;
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

void ASCharacter::TakeObject()
{
	if (CurrentTakenActor) return;
	FVector Location;
	FRotator Rotation;
	Controller->GetPlayerViewPoint(Location, Rotation);

	const auto StartPoint = Location;
	const auto Direction = Rotation.Vector();
	const auto EndPoint = StartPoint + RangeOfTakenObject * Direction;
	DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 2.0f, 0, 3.0f);
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility, CollisionParams);

	if (!HitResult.bBlockingHit) return;

	const auto HittedObject = Cast<ABaseChangeableActor>(HitResult.GetActor());
	if (!HittedObject) return;

	CurrentTakenActor = HittedObject;
	CurrentTakenActor->DisableCurrentMeshPhysics();
	const auto AttachmentRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	CurrentTakenActor->AttachToComponent(GetMesh(), AttachmentRules, AttachObjectSocketName);
	CurrentTakenActor->SetMeshChangeable(false);
}

void ASCharacter::DropObject()
{
	if (!CurrentTakenActor) return;

	const auto DetachmentRules = FDetachmentTransformRules::KeepWorldTransform;
	CurrentTakenActor->DetachFromActor(DetachmentRules);
	CurrentTakenActor->SetMeshChangeable(true);
	CurrentTakenActor->EnableCurrentMeshPhysics();
	CurrentTakenActor = nullptr;
	
}

void ASCharacter::OnOpenJournal()
{
	const auto PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController) return;
	OnJournalOpen.Broadcast();
	PlayerController->SetShowMouseCursor(true);
	PlayerController->SetInputMode(FInputModeUIOnly::FInputModeUIOnly());
}