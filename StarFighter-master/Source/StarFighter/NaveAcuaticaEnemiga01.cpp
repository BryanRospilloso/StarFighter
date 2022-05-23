// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAcuaticaEnemiga01.h"

ANaveAcuaticaEnemiga01::ANaveAcuaticaEnemiga01()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NaveEnemigaAcuatica(TEXT("/Engine/BasicShapes/Cone.Cone"));


	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipMeshComponent->SetStaticMesh(NaveEnemigaAcuatica.Object);

	fBurstDelay = 0.15f;

}

void ANaveAcuaticaEnemiga01::BeginPlay()
{
	Super::BeginPlay();

	TotalTime = 0.0f;

	TimeSinceLastShot = 0.0f;

	fDestroyTimer = 1.0f;

	ThisWorld = GetWorld();

	RandomStart = FMath::Rand();

	OnActorBeginOverlap.AddDynamic(this, &ANaveAcuaticaEnemiga01::OnBeginOverlap);

}

void ANaveAcuaticaEnemiga01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Current_Location = this->GetActorLocation();
	Current_Rotation = this->GetActorRotation();

	Current_Location.X += FMath::Sin(TotalTime + RandomStart);

	this->SetActorLocation(Current_Location - (Current_Velocity * DeltaTime));

	//handle shooting

	TotalTime += DeltaTime;
	TimeSinceLastShot += DeltaTime;

	if (TimeSinceLastShot >= 1.0f && !bHit) {

		if (fBurstDelay >= 0.05f) {

			FActorSpawnParameters Params = {};
			Params.Owner = this;

			GetWorld()->SpawnActor(Projectile_BombaEnemigo_BP, &Current_Location, &Current_Rotation, Params);

			fBurstDelay = 0.0f;

		}

		TimeSinceLastShot = 0.0f;
		fBurstDelay += DeltaTime;

	}

}

void ANaveAcuaticaEnemiga01::OnBeginOverlap(AActor* EnemigoActor, AActor* OtherActor)
{
}
