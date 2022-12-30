// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChaosD.h"
#include "GameFramework/Actor.h"
#include "EnterChaosD.generated.h"

UCLASS()
class CHAOSD_API AEnterChaosD : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnterChaosD();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnyWhere,Category=Box)
	UBoxComponent* EnterChaosDBoxComponent;

	UPROPERTY(VisibleAnyWhere, Category = Box)
	UStaticMeshComponent* EnterChaosDComponent;

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	

};
