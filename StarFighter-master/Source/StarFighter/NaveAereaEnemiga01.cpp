// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAereaEnemiga01.h"
#include "Proyectil_Bala.h"
#include "Proyectil_Bomba.h"
#include "Proyectil_Misil.h"
#include "Proyectil_Rayo.h"

ANaveAereaEnemiga01::ANaveAereaEnemiga01()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NaveEnemigaAerea(TEXT("/Engine/BasicShapes/Cone.Cone"));


	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipMeshComponent->SetStaticMesh(NaveEnemigaAerea.Object);

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 10.0f;
	bCanFire = true;

	//FireForwardValue = 10.0f;
	//FireRightValue = 100.0f;

}

void ANaveAereaEnemiga01::BeginPlay()
{
	Super::BeginPlay();

	TotalTime = 60.0f;

	bHit = false;
	bDead = false;

	RandomStart = FMath::Rand();

	ThisWorld = GetWorld();

}

void ANaveAereaEnemiga01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Spawn projectile at an offset from this pawn
	const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

	Current_Location = this->GetActorLocation();
	Current_Rotation = this->GetActorRotation();

	Current_Location.Y += FMath::Sin(TotalTime + RandomStart);
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
				World->SpawnActor<AProyectil_Misil>(SpawnLocation, FireRotation);

			}
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAereaEnemiga01::ShotTimerExpired, FireRate);
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
	}

}

void ANaveAereaEnemiga01::FireMisil()
{
	bCanFire = true;

}

void ANaveAereaEnemiga01::ShotTimerExpired()
{
	bCanFire = true;

}

void ANaveAereaEnemiga01::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	AProyectil_Bala* InventoryItemBala = Cast<AProyectil_Bala>(Other);
	if (InventoryItemBala != nullptr)
	{
		bDead = true;

	}

	AProyectil_Bomba* InventoryItemBomba = Cast<AProyectil_Bomba>(Other);
	if (InventoryItemBomba != nullptr)
	{
		bDead = true;
		
	}

	AProyectil_Misil* InventoryItemMisil = Cast<AProyectil_Misil>(Other);
	if (InventoryItemMisil != nullptr)
	{
		bDead = true;

	}

	AProyectil_Rayo* InventoryItemRayo = Cast<AProyectil_Rayo>(Other);
	if (InventoryItemRayo != nullptr)
	{
		bDead = true;

	}

}
