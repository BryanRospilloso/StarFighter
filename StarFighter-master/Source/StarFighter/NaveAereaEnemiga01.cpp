// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAereaEnemiga01.h"

ANaveAereaEnemiga01::ANaveAereaEnemiga01()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NaveEnemigaAerea(TEXT("/Engine/BasicShapes/Cone.Cone"));


	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipMeshComponent->SetStaticMesh(NaveEnemigaAerea.Object);

	fBurstDelay = 0.15f;

}

void ANaveAereaEnemiga01::BeginPlay()
{
	Super::BeginPlay();

	TotalTime = 0.0f;

	TimeSinceLastShot = 0.0f;

	fDestroyTimer = 1.0f;

	ThisWorld = GetWorld();

	RandomStart = FMath::Rand();

}

void ANaveAereaEnemiga01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Current_Location = this->GetActorLocation();
	Current_Rotation = this->GetActorRotation();

	Current_Location.Y += FMath::Sin(TotalTime + RandomStart);
	Current_Location.X += FMath::Sin(TotalTime + RandomStart);

	this->SetActorLocation(Current_Location - (Current_Velocity * DeltaTime));

	//handle shooting

	TotalTime += DeltaTime;
	TimeSinceLastShot += DeltaTime;

	if (TimeSinceLastShot >= 1.0f && !bHit) {

		if (fBurstDelay >= 0.05f) {

			FActorSpawnParameters Params = {};
			Params.Owner = this;

			GetWorld()->SpawnActor(Projectile_MisilEnemigo_BP, &Current_Location, &Current_Rotation, Params);

			fBurstDelay = 0.0f;

		}

		TimeSinceLastShot = 0.0f;
		fBurstDelay += DeltaTime;

	}

}
