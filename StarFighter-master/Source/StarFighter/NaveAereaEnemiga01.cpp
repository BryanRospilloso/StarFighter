// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAereaEnemiga01.h"
#include "Proyectil_Bala.h"
#include "Proyectil_Bomba.h"
#include "Proyectil_Misil.h"
#include "Proyectil_Rayo.h"
#include "Publisher.h"
#include "ClockTower.h"

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

	this->SetActorLocation(Current_Location + (Current_Velocity * DeltaTime));

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

void ANaveAereaEnemiga01::Destroyed()
{
	Super::Destroyed();
	//Log Error if its Clock Tower is NULL
	if (!ClockTower) { UE_LOG(LogTemp, Error, TEXT("Destroyed():ClockTower is NULL, make sure it's initialized.")); return; }
	//Unsubscribe from the Clock Tower if it's destroyed
	ClockTower->UnSubscribe(this);
}

void ANaveAereaEnemiga01::Update(APublisher* Publisher)
{
	//Execute the routine
	Morph();
}

void ANaveAereaEnemiga01::Morph()
{
	//Log Error if its Clock Tower is NULL
	if (!ClockTower) { UE_LOG(LogTemp, Error, TEXT("Morph():ClockTower is NULL, make sure it's initialized.")); return; }

	//Get the current time of the Clock Tower
	FString Time = ClockTower->GetTime();

	if (!Time.Compare("Enemigo Estatico"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::Printf(TEXT("El Enemigo se encuentra Estatico"), *Time));
	}
	else if (!Time.Compare("Enemigo en Movimiento"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::Printf(TEXT("El Enemigo se encuentra en Movimiento"), *Time));
	}
	else if (!Time.Compare("Enemigo Atacando"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("El Enemigo esta Disparando"), *Time));
	}
	else if (!Time.Compare("Nave Amiga"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("La nave es aliada"), *Time));
	}
}

void ANaveAereaEnemiga01::SetClockTower(AClockTower* myClockTower)
{
	//Log Error if the passed Clock Tower is NULL
	if (!myClockTower) { UE_LOG(LogTemp, Error, TEXT("SetClockTower(): myClockTower is NULL, make sure it's initialized.")); return; }
	//Set the Clock Tower and Subscribe to that
	ClockTower = myClockTower;
	ClockTower->Subscribe(this);
}
