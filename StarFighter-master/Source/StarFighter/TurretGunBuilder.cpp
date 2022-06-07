// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretGunBuilder.h"
#include "Torretas.h"

// Sets default values
ATurretGunBuilder::ATurretGunBuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurretGunBuilder::BeginPlay()
{
	Super::BeginPlay();

	//Spawn the Torretas Actors
	Torretas = GetWorld()->SpawnActor<ATorretas>(ATorretas::StaticClass());

	//Attach it to the Builder (this)
	Torretas->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called every frame
void ATurretGunBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurretGunBuilder::BuildSoporteTorreta()
{
	if (!Torretas)
	{
		UE_LOG(LogTemp, Error, TEXT("BuildSoporteTorreta():Torretas is NULL, make sure it's initialized."));
		return;
	}

	//Set de Soporte Torreta of the Torreta
	Torretas->SetSoporteTorreta("Soporte Torreta");
}

void ATurretGunBuilder::BuildCuerpoTorreta()
{
	if (!Torretas)
	{
		UE_LOG(LogTemp, Error, TEXT("BuildCuerpoTorreta():Torretas is NULL, make sure it's initialized."));
		return;
	}

	//Set de Cuerpo Torreta of the Torreta
	Torretas->SetCuerpoTorreta("Cuerpo Torreta");
}

void ATurretGunBuilder::BuildArmasTorreta()
{
	if (!Torretas)
	{
		UE_LOG(LogTemp, Error, TEXT("BuildArmasTorreta():Torretas is NULL, make sure it's initialized."));
		return;
	}

	//Set de Soporte Torreta of the Torreta
	Torretas->SetArmasTorreta("Armas Torreta");
}

ATorretas* ATurretGunBuilder::GetTorretas()
{
	//Returns the Torretas Actor of the Builder (this)
	return Torretas;
}

