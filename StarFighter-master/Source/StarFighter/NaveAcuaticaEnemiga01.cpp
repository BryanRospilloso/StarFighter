// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAcuaticaEnemiga01.h"
#include "Proyectil_Bala.h"
#include "Proyectil_Bomba.h"
#include "Proyectil_Misil.h"
#include "Proyectil_Rayo.h"

ANaveAcuaticaEnemiga01::ANaveAcuaticaEnemiga01()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NaveEnemigaAcuatica(TEXT("/Engine/BasicShapes/Cone.Cone"));


	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipMeshComponent->SetStaticMesh(NaveEnemigaAcuatica.Object);

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 10.0f;
	bCanFire = true;

	//FireForwardValue = 10.0f;
	//FireRightValue = 100.0f;

}

void ANaveAcuaticaEnemiga01::BeginPlay()
{
	Super::BeginPlay();

	TotalTime = 60.0f;

	bHit = false;
	bDead = false;
	NaveDestruida = false;

	RandomStart = FMath::Rand();

	ThisWorld = GetWorld();

}

void ANaveAcuaticaEnemiga01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Spawn projectile at an offset from this pawn
	const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

	Current_Location = this->GetActorLocation();
	Current_Rotation = this->GetActorRotation();

	Current_Location.X += FMath::Sin(TotalTime + RandomStart);

	this->SetActorLocation(Current_Location - (Current_Velocity * DeltaTime));

	TimeSinceLastShot += DeltaTime;

	if (TimeSinceLastShot >= 1.0f) {
		if (bCanFire == true)
		{

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// spawn the projectile
				World->SpawnActor<AProyectil_Bomba>(SpawnLocation, FireRotation);

			}
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAcuaticaEnemiga01::ShotTimerExpired, FireRate);
			bCanFire = true;

		}
		TimeSinceLastShot = 0.0f;
	}

	if (bHit)
	{
		ShipMeshComponent->SetVisibility(false);
		this->SetActorEnableCollision(false);

	}
	if (bDead)
	{
		this->Destroy();
		SetEstadoNave();
	}

}

void ANaveAcuaticaEnemiga01::FireBomba()
{
	bCanFire = true;

}

void ANaveAcuaticaEnemiga01::ShotTimerExpired()
{
	bCanFire = true;

}

void ANaveAcuaticaEnemiga01::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	AProyectil_Bala* InventoryItemBala = Cast<AProyectil_Bala>(Other);
	if (InventoryItemBala != nullptr)
	{
		if (ThisWorld)
		{
			bHit = true;
			FVector CurrentSpawnLocation = this->GetActorLocation();
			FRotator CurrentSpawnRotation = this->GetActorRotation();
			FActorSpawnParameters Params = {};

			ThisWorld->SpawnActor(Pickup1, &CurrentSpawnLocation, &CurrentSpawnRotation, Params);
			ThisWorld->SpawnActor(Pickup2, &CurrentSpawnLocation, &CurrentSpawnRotation, Params);

			bDead = true;

		}

	}

	AProyectil_Bomba* InventoryItemBomba = Cast<AProyectil_Bomba>(Other);
	if (InventoryItemBomba != nullptr)
	{
		if (ThisWorld)
		{
			bHit = true;
			FVector CurrentSpawnLocation = this->GetActorLocation();
			FRotator CurrentSpawnRotation = this->GetActorRotation();
			FActorSpawnParameters Params = {};

			ThisWorld->SpawnActor(Pickup1, &CurrentSpawnLocation, &CurrentSpawnRotation, Params);
			ThisWorld->SpawnActor(Pickup2, &CurrentSpawnLocation, &CurrentSpawnRotation, Params);

			bDead = true;
		}

	}

	AProyectil_Misil* InventoryItemMisil = Cast<AProyectil_Misil>(Other);
	if (InventoryItemMisil != nullptr)
	{
		if (ThisWorld)
		{
			bHit = true;
			FVector CurrentSpawnLocation = this->GetActorLocation();
			FRotator CurrentSpawnRotation = this->GetActorRotation();
			FActorSpawnParameters Params = {};

			ThisWorld->SpawnActor(Pickup1, &CurrentSpawnLocation, &CurrentSpawnRotation, Params);
			ThisWorld->SpawnActor(Pickup2, &CurrentSpawnLocation, &CurrentSpawnRotation, Params);

			bDead = true;
		}

	}

	AProyectil_Rayo* InventoryItemRayo = Cast<AProyectil_Rayo>(Other);
	if (InventoryItemRayo != nullptr)
	{
		if (ThisWorld)
		{
			bHit = true;
			FVector CurrentSpawnLocation = this->GetActorLocation();
			FRotator CurrentSpawnRotation = this->GetActorRotation();
			FActorSpawnParameters Params = {};

			ThisWorld->SpawnActor(Pickup1, &CurrentSpawnLocation, &CurrentSpawnRotation, Params);
			ThisWorld->SpawnActor(Pickup2, &CurrentSpawnLocation, &CurrentSpawnRotation, Params);

			bDead = true;
		}

	}

}

void ANaveAcuaticaEnemiga01::SetEstadoNave()
{
	NaveDestruida = true;
}
