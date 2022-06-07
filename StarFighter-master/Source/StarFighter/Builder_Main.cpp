// Fill out your copyright notice in the Description page of Project Settings.


#include "Builder_Main.h"
#include "TurretGunBuilder.h"
#include "GunMechanic.h"
#include "Torretas.h"

// Sets default values
ABuilder_Main::ABuilder_Main()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuilder_Main::BeginPlay()
{
	Super::BeginPlay();

	//Spawn Builder and Mechanic
	TurretBuilder = GetWorld()->SpawnActor<ATurretGunBuilder>(ATurretGunBuilder::StaticClass());
	Mechanic = GetWorld()->SpawnActor<AGunMechanic>(AGunMechanic::StaticClass());

	//Set the Builder for the Mechanic and create the buildings
	Mechanic->SetTorretasBuilder(TurretBuilder);
	Mechanic->ConstructTorretas();

	//Get the Mechanic's Torretas and Logs the creates buildings
	ATorretas* Torretas = Mechanic->GetTorretas();
	Torretas->TorretasCharacteristics();
	
}

// Called every frame
void ABuilder_Main::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

