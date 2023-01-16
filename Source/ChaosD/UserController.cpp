// Fill out your copyright notice in the Description page of Project Settings.

#include "UserController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "UserCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "MenuWidget.h"

AUserController::AUserController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	static ConstructorHelpers::FClassFinder<UMenuWidget>UI_TEST_C(TEXT("/Game/UI/TESTUI.TESTUI_C"));
	//static ConstructorHelpers::FClassFinder<UMenuWidget>UI_TEST_C(TEXT("/Game/UI/UI_TEST2.UI_TEST2_C"));
	
	if (UI_TEST_C.Succeeded())
	{
		MenuWidgetClass = UI_TEST_C.Class;
	}
	
}

void AUserController::BeginPlay()
{
	Super::BeginPlay();
	ChangeInputGameMode(true);

	//test
	MenuWidget = CreateWidget<UMenuWidget>(this,MenuWidgetClass);
	MenuWidget->AddToViewport();
	MenuWidget->SetVisibility(ESlateVisibility::Visible);
}

void AUserController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bInputPressed)
	{
		FollowTime += DeltaTime;

		// Look for the touch location
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		if (bIsTouch)
		{
			GetHitResultUnderFinger(ETouchIndex::Touch1, ECC_Visibility, true, Hit);
		}
		else
		{
			GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		}
		HitLocation = Hit.Location;

		// Direct the Pawn towards that location
		APawn* const MyPawn = GetPawn();
		if (MyPawn)
		{
			FVector WorldDirection = (HitLocation - MyPawn->GetActorLocation()).GetSafeNormal();
			MyPawn->AddMovementInput(WorldDirection, 1.f, false);
		}
	}
	else
	{
		FollowTime = 0.f;
	}
}

void AUserController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("TEST"), IE_Pressed, this, &AUserController::TestUII);
	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AUserController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AUserController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AUserController::OnTouchPressed);
	InputComponent->BindTouch(EInputEvent::IE_Released, this, &AUserController::OnTouchReleased);

}

void AUserController::OnSetDestinationPressed()
{
	// We flag that the input is being pressed
	bInputPressed = true;
	// Just in case the character was moving because of a previous short press we stop it
	//StopMovement();
}

void AUserController::OnSetDestinationReleased()
{
	// Player is no longer pressing the input
	bInputPressed = false;

	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We look for the location in the world where the player has pressed the input
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		HitLocation = Hit.Location;

		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitLocation);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, HitLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
}

void AUserController::OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = true;
	OnSetDestinationPressed();
}

void AUserController::OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AUserController::ChangeInputGameMode(bool bGameMode)
{
	if(bGameMode)
	{
		SetInputMode(GameOnly);
	}
	else
	{
		SetInputMode(UIOnly);
	}
}


void AUserController::TestUII()
{
	try
	{
		MenuWidget->SetVisibility(ESlateVisibility::Hidden);
		MenuWidget = nullptr;
	}
	catch (...)
	{
		std::cout<<"asd";
	}
	
	
	
		
	
	
	
	
	//ChangeInputGameMode(false);
}
