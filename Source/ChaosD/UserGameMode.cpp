// Fill out your copyright notice in the Description page of Project Settings.


#include "UserGameMode.h"
#include "UserCharacter.h"
#include "UserController.h"

AUserGameMode::AUserGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUserController::StaticClass();
	DefaultPawnClass = AUserCharacter::StaticClass();
}