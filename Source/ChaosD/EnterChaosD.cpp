// Fill out your copyright notice in the Description page of Project Settings.


#include "EnterChaosD.h"

// Sets default values
AEnterChaosD::AEnterChaosD()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EnterChaosDBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ENTERChAOSDBOXCOMPONENT"));
	EnterChaosDComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ENTERChAOSDCOMPONENT"));
	

	RootComponent = EnterChaosDBoxComponent;
	EnterChaosDComponent->SetupAttachment(EnterChaosDBoxComponent);

	EnterChaosDBoxComponent->SetBoxExtent(FVector(200.0f, 200.0f, 250.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> OB_ENTER_CHAOSD(TEXT("/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Statues/StaticMesh/SM_Plains_Angel_Statue_01_nobase"));
	if (OB_ENTER_CHAOSD.Succeeded())
	{
		EnterChaosDComponent->SetStaticMesh(OB_ENTER_CHAOSD.Object);
	}

	EnterChaosDComponent->SetRelativeLocation(FVector(0.0f, -3.5f, 0.0f));

	EnterChaosDBoxComponent->SetCollisionProfileName(TEXT("EnterChaos"));
	EnterChaosDComponent->SetCollisionProfileName(TEXT("NoCollision")); //BlockAllDynamic
	
}

// Called when the game starts or when spawned
void AEnterChaosD::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnterChaosD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnterChaosD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	EnterChaosDBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnterChaosD::OnCharacterOverlap);
	EnterChaosDComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnterChaosD::OnCharacterOverlap);
}

void AEnterChaosD::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABLOG_S(Warning);
}


