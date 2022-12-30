// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChaosD.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHAOSD_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
};
