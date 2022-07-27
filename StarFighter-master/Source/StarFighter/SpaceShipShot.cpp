// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShipShot.h"

// Sets default values
ASpaceShipShot::ASpaceShipShot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ProjectileBala

	bBalaIsFiring = false;
	FireBalaRate = 0.25f;
	BalaTimeSinceLastShot = 0.0f;

}

// Called when the game starts or when spawned
void ASpaceShipShot::BeginPlay()
{
	Super::BeginPlay();

	ThisWorld = GetWorld();
	
}

// Called every frame
void ASpaceShipShot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ProjectileBala

	if (bBalaIsFiring)
	{
		if (BalaTimeSinceLastShot > FireBalaRate)
		{
			FireWeaponBala();
			BalaTimeSinceLastShot = 0.0f;
		}
	}

	BalaTimeSinceLastShot += DeltaTime;

}

// Called to bind functionality to input
void ASpaceShipShot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(FName("Fire"), IE_Pressed, this, &ASpaceShipShot::StartFiringBala);
	PlayerInputComponent->BindAction(FName("Fire"), IE_Released, this, &ASpaceShipShot::StopFiringBala);

}

//ProjectileBala

void ASpaceShipShot::StartFiringBala()
{
	bBalaIsFiring = true;

}

void ASpaceShipShot::StopFiringBala()
{
	bBalaIsFiring = false;

}

void ASpaceShipShot::FireWeaponBala()
{
	/*FActorSpawnParameters Params = {};
	Params.Owner = this;

	AActor* SpawnedProjectileBala = GetWorld()->SpawnActor(Proyectil_Bala_BP,
		&Current_Location, &Current_Rotation, Params);*/

	if (ThisWorld)
	{
		FVector CurrentSpawnLocation = this->GetActorLocation();
		FRotator CurrentSpawnRotation = this->GetActorRotation();
		FActorSpawnParameters Params = {};

		ThisWorld->SpawnActor(Proyectil_Bala_BP, &CurrentSpawnLocation, &CurrentSpawnRotation, Params);

	}

}

void ASpaceShipShot::Fire()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, TEXT("El arma esta disparando"));
}