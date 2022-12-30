// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChaosD.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "UserController.generated.h"
class UNiagaraSystem;

UCLASS()
class CHAOSD_API AUserController : public APlayerController
{
	GENERATED_BODY()

public:
	AUserController();
	void ChangeInputGameMode(bool bGameMode= true);

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;
	
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;
	virtual void BeginPlay() override;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=UI)
	TSubclassOf<class UMenuWidget>MenuWidgetClass;

	

	

private:
	void TestUII();
	bool bInputPressed; // Input is bring pressed
	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed

	UPROPERTY()
	class UMenuWidget* MenuWidget;

	FInputModeGameOnly GameOnly;
	FInputModeUIOnly UIOnly;

	
};
