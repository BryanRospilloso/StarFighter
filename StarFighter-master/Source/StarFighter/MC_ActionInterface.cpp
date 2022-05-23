// Fill out your copyright notice in the Description page of Project Settings.


#include "MC_ActionInterface.h"

IMC_ActionInterface::IMC_ActionInterface()
{
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> NaveEnemigaTerrestre(TEXT("/Engine/BasicShapes/Cone.Cone"));


	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//ShipMeshComponent->SetStaticMesh(NaveEnemigaTerrestre.Object);
	
	fBurstDelay = 0.15f;

}

inline void IMC_ActionInterface::BeginPlay() { 

	//Super::BeginPlay();

	TotalTime = 0.0f;

	TimeSinceLastShot = 0.0f;

	fDestroyTimer = 1.0f;

	//ThisWorld = GetWorld();

	RandomStart = FMath::Rand();

	//OnActorBeginOverlap.AddDynamic(this, &ANaveTerrestreEnemiga01::OnBeginOverlap);

}

inline void IMC_ActionInterface::Tick(float DeltaTime) { 

	//Super::Tick(DeltaTime);

	//Current_Location = this->GetActorLocation();
	//Current_Rotation = this->GetActorRotation();

	Current_Location.Y += FMath::Sin(TotalTime + RandomStart);

	//this->SetActorLocation(Current_Location - (Current_Velocity * DeltaTime));

	//handle shooting

	TotalTime += DeltaTime;
	TimeSinceLastShot += DeltaTime;

	if (TimeSinceLastShot >= 1.0f && !bHit) {

		if (fBurstDelay >= 0.05f) {

			FActorSpawnParameters Params = {};
			//Params.Owner = this;

			//GetWorld()->SpawnActor(Projectile_BalaEnemigo_BP, &Current_Location, &Current_Rotation, Params);

			fBurstDelay = 0.0f;

		}

		TimeSinceLastShot = 0.0f;
		fBurstDelay += DeltaTime;

	}
}



