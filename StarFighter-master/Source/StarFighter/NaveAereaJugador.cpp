// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAereaJugador.h"
#include "Proyectil.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ANaveAereaJugador::ANaveAereaJugador()
{
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	ShipInventory = CreateDefaultSubobject<UInventoryComponent>("MyInventory");

	// Movement
	MoveSpeed = 1000.0f;

	// Health
	Vida = 5;

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = false;

	FireForwardValue = 1.0f;
	FireRightValue = 0.0f;

	//Ship info
	ShipInfo.Add("Vida", 0);
	ShipInfo.Add("Velocidad", 0);
	ShipInfo.Add("RestarVida", 0);
	ShipInfo.Add("RestarVelocidad", 0);
	ShipInfo.Add("DisparoRapido", 0);
	ShipInfo.Add("DisparoLento", 0);

	MaxVelocity = 500.0f;
	Current_X_Velocity = 0.0f;
	Current_Y_Velocity = 0.0f;

	//ProjectileBala

	bBalaIsFiring = false;
	FireBalaRate = 0.25f;
	BalaTimeSinceLastShot = 0.0f;

	//ProjectileBomba

	bBombaIsFiring = false;
	FireBombaRate = 1.0f;
	BombaTimeSinceLastShot = 0.0f;

	//ProjectileMisil

	bMisilIsFiring = false;
	FireMisilRate = 2.0f;
	MisilTimeSinceLastShot = 0.0f;

	//ProjectileRayo

	bRayoIsFiring = false;
	FireRayoRate = 1.25f;
	RayoTimeSinceLastShot = 0.0f;

}

void ANaveAereaJugador::BeginPlay()
{
	Super::BeginPlay();

	Current_Location = this->GetActorLocation();
	Current_Rotation = this->GetActorRotation();

}


void ANaveAereaJugador::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);

	PlayerInputComponent->BindAxis(FName("MoveUp"), this, &ANaveAereaJugador::MoveUp);
	PlayerInputComponent->BindAxis(FName("MoveHorizontal"), this, &ANaveAereaJugador::MoveRight);
	PlayerInputComponent->BindAction(FName("FireBala"), IE_Pressed, this, &ANaveAereaJugador::StartFiringBala);
	PlayerInputComponent->BindAction(FName("FireBala"), IE_Released, this, &ANaveAereaJugador::StopFiringBala);
	PlayerInputComponent->BindAction(FName("FireBomba"), IE_Pressed, this, &ANaveAereaJugador::StartFiringBomba);
	PlayerInputComponent->BindAction(FName("FireBomba"), IE_Released, this, &ANaveAereaJugador::StopFiringBomba);
	PlayerInputComponent->BindAction(FName("FireMisil"), IE_Pressed, this, &ANaveAereaJugador::StartFiringMisil);
	PlayerInputComponent->BindAction(FName("FireMisil"), IE_Released, this, &ANaveAereaJugador::StopFiringMisil);
	PlayerInputComponent->BindAction(FName("FireRayo"), IE_Pressed, this, &ANaveAereaJugador::StartFiringRayo);
	PlayerInputComponent->BindAction(FName("FireRayo"), IE_Released, this, &ANaveAereaJugador::StopFiringRayo);
	
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ANaveAereaJugador::Fire);
	PlayerInputComponent->BindAction(TEXT("DropItem"), EInputEvent::IE_Pressed, this, &ANaveAereaJugador::DropItem);
	PlayerInputComponent->BindAction(TEXT("ShowInventory"), IE_Pressed, this, &ANaveAereaJugador::ShowInventory);
	PlayerInputComponent->BindAction(TEXT("ConsumirVelocidad"), IE_Pressed, this, &ANaveAereaJugador::ConsumirVelocidad);
	PlayerInputComponent->BindAction(TEXT("ConsumirVida"), IE_Pressed, this, &ANaveAereaJugador::ConsumirVida);
	PlayerInputComponent->BindAction(TEXT("DisminuirVelocidad"), IE_Pressed, this, &ANaveAereaJugador::DisminuirVelocidad);
	PlayerInputComponent->BindAction(TEXT("DisminuirVida"), IE_Pressed, this, &ANaveAereaJugador::DisminuirVida);
	PlayerInputComponent->BindAction(TEXT("FastShoot"), IE_Pressed, this, &ANaveAereaJugador::FastShoot);
	PlayerInputComponent->BindAction(TEXT("SlowShoot"), IE_Pressed, this, &ANaveAereaJugador::SlowShoot);

}

void ANaveAereaJugador::MoveUp(float AxisValue)
{
	Current_X_Velocity = MaxVelocity * AxisValue;

}

void ANaveAereaJugador::MoveRight(float AxisValue)
{
	Current_Y_Velocity = MaxVelocity * AxisValue;

}

void ANaveAereaJugador::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (Current_X_Velocity != 0.0f || Current_Y_Velocity != 0.0f)
	{
		New_Location = FVector(Current_Location.X + (Current_X_Velocity * DeltaSeconds),
			Current_Location.Y + (Current_Y_Velocity * DeltaSeconds), 0);

		this->SetActorLocation(New_Location);

		Current_Location = New_Location;

	}

	//ProjectileBala

	if (bBalaIsFiring)
	{
		if (BalaTimeSinceLastShot > FireBalaRate)
		{
			FireWeaponBala();
			BalaTimeSinceLastShot = 0.0f;
		}
	}

	BalaTimeSinceLastShot += DeltaSeconds;

	//ProjectileBomba

	if (bBombaIsFiring)
	{
		if (BombaTimeSinceLastShot > FireBombaRate)
		{
			FireWeaponBomba();
			BombaTimeSinceLastShot = 0.0f;
		}
	}

	BombaTimeSinceLastShot += DeltaSeconds;

	//ProjectileMisil

	if (bMisilIsFiring)
	{
		if (MisilTimeSinceLastShot > FireMisilRate)
		{
			FireWeaponMisil();
			MisilTimeSinceLastShot = 0.0f;
		}
	}

	MisilTimeSinceLastShot += DeltaSeconds;

	//ProjectileRayo

	if (bRayoIsFiring)
	{
		if (RayoTimeSinceLastShot > FireRayoRate)
		{
			FireWeaponRayo();
			RayoTimeSinceLastShot = 0.0f;
		}
	}

	RayoTimeSinceLastShot += DeltaSeconds;
	
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	if (ForwardValue != 0.0f || RightValue != 0.0f) {

		if (ForwardValue != FireForwardValue) {
			FireForwardValue = ForwardValue;
		}

		if (RightValue != FireRightValue) {
			FireRightValue = RightValue;
		}
	}

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}

}

void ANaveAereaJugador::Fire() {
	bCanFire = true;
	UE_LOG(LogTemp, Warning, TEXT("Se presiono la barra espaciadora"));
	// Create fire direction vector
	
	UE_LOG(LogTemp, Warning, TEXT("FireForwardValue: %f FireRightValue: %f"), FireForwardValue, FireRightValue);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	// Try and fire a shot
	FireShot(FireDirection);
}

void ANaveAereaJugador::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		
		// If we are pressing fire stick in a direction
		//if (FireDirection.SizeSquared() > 0.0f)
		//{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// spawn the projectile
				World->SpawnActor<AProyectil>(SpawnLocation, FireRotation);
				//UE_LOG(LogTemp, Warning, TEXT("SpawnLocation(X, Y) = %s, %s FireRotation(X, Y) =  s, s"), SpawnLocation.X, SpawnLocation.Y);
				//UE_LOG(LogTemp, Warning, TEXT("World not nullptr"));
			}

			

			//bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAereaJugador::ShotTimerExpired, FireRate);

			// try and play the sound if specified

		/*	if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}*/

			bCanFire = false;
		//}
	}
}

void ANaveAereaJugador::ShotTimerExpired()
{
	bCanFire = true;
}

void ANaveAereaJugador::DropItem()
{
	if (ShipInventory->CurrentInventory.Num() == 0)
	{
		return;
	}
	AInventoryActor* Item = ShipInventory->CurrentInventory.Last();
	ShipInventory->RemoveFromInventory(Item);
	//should probably use scaled bounding box
	FVector ItemOrigin;
	FVector ItemBounds;
	Item->GetActorBounds(false, ItemOrigin, ItemBounds);
	FTransform PutDownLocation = GetTransform() + FTransform(RootComponent->GetForwardVector() * ItemBounds.GetMax());
	Item->PutDown(PutDownLocation);
}

void ANaveAereaJugador::TakeItem(AInventoryActor* InventoryItem)
{
	InventoryItem->PickUp();
	ShipInventory->AddToInventory(InventoryItem);
}

void ANaveAereaJugador::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, 
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	AInventoryActor* InventoryItem = Cast<AInventoryActor>(Other);
	if (InventoryItem != nullptr)
	{
		FString n = InventoryItem->GetInventoryActorName();
		for (auto& pair : ShipInfo)
		{
			if (pair.Key == n)
			{
				pair.Value += 1;
				break;

			}
		}

		TakeItem(InventoryItem);

	}
}

void ANaveAereaJugador::ShowInventory()
{
	/*for (auto It = ShipInventory->CurrentInventory.CreateConstIterator(); It; ++It)
	{
		FString n = Cast<AInventoryActor>(*It)->GetInventoryActorName();

		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Actor de nombre: %s"), *n));

	}*/

	for (auto& Elem : ShipInfo)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));
	}

}

void ANaveAereaJugador::Test()
{
	//TSet<int> EjemploSet;
	//for (auto It = EjemploSet.CreateConstIterator(); It; ++It)
	//{
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));
	//}

}

void ANaveAereaJugador::ConsumirVelocidad()
{
	FString n = "Velocidad";
	for (auto& pair : ShipInfo)
	{
		if (pair.Key == n)
		{
			if (pair.Value > 0)
			{
				pair.Value = pair.Value - 1;
				MaxVelocity = MaxVelocity + 500;
				
			}
			break;
		}
	}

}

void ANaveAereaJugador::ConsumirVida()
{
	FString n = "Vida";
	for (auto& pair : ShipInfo)
	{
		if (pair.Key == n)
		{
			if (pair.Value > 0)
			{
				pair.Value = pair.Value - 1;
				Vida = Vida + 1;
				UE_LOG(LogTemp, Warning, TEXT("Mas una vida"));

			}
			break;
		}
	}

}

void ANaveAereaJugador::DisminuirVelocidad()
{
	FString n = "RestarVelocidad";
	for (auto& pair : ShipInfo)
	{
		if (pair.Key == n)
		{
			if (pair.Value > 0)
			{
				pair.Value = pair.Value - 1;
				MaxVelocity = MaxVelocity - 500;
				
			}
			break;
		}
	}

}

void ANaveAereaJugador::DisminuirVida()
{
	FString n = "RestarVida";
	for (auto& pair : ShipInfo)
	{
		if (pair.Key == n)
		{
			if (pair.Value > 0)
			{
				pair.Value = pair.Value - 1;
				Vida = Vida - 1;
				UE_LOG(LogTemp, Warning, TEXT("Menos una vida"));

			}
			break;
		}
	}

}

void ANaveAereaJugador::FastShoot()
{
	FString n = "DisparoRapido";
	for (auto& pair : ShipInfo)
	{
		if (pair.Key == n)
		{
			if (pair.Value > 0)
			{
				pair.Value = pair.Value - 1;
				FireBalaRate = FireBalaRate - 0.08;

			}
			break;
		}
	}

}

void ANaveAereaJugador::SlowShoot()
{
	FString n = "DisparoLento";
	for (auto& pair : ShipInfo)
	{
		if (pair.Key == n)
		{
			if (pair.Value > 0)
			{
				pair.Value = pair.Value - 1;
				FireBalaRate = FireBalaRate + 0.1;

			}
			break;
		}
	}

}

//ProjectileBala

void ANaveAereaJugador::StartFiringBala()
{
	bBalaIsFiring = true;

}

void ANaveAereaJugador::StopFiringBala()
{
	bBalaIsFiring = false;

}

void ANaveAereaJugador::FireWeaponBala()
{
	FActorSpawnParameters Params = {};
	Params.Owner = this;

	AActor* SpawnedProjectileBala = GetWorld()->SpawnActor(Projectile_Bala_BP,
		&Current_Location, &Current_Rotation, Params);

}

//ProjectileBomba

void ANaveAereaJugador::StartFiringBomba()
{
	bBombaIsFiring = true;

}

void ANaveAereaJugador::StopFiringBomba()
{
	bBombaIsFiring = false;

}

void ANaveAereaJugador::FireWeaponBomba()
{
	FActorSpawnParameters Params = {};
	Params.Owner = this;

	AActor* SpawnedProjectileBomba = GetWorld()->SpawnActor(Projectile_Bomba_BP,
		&Current_Location, &Current_Rotation, Params);

}

//ProjectileMisil

void ANaveAereaJugador::StartFiringMisil()
{
	bMisilIsFiring = true;

}

void ANaveAereaJugador::StopFiringMisil()
{
	bMisilIsFiring = false;

}

void ANaveAereaJugador::FireWeaponMisil()
{
	FActorSpawnParameters Params = {};
	Params.Owner = this;

	AActor* SpawnedProjectileMisil = GetWorld()->SpawnActor(Projectile_Misil_BP,
		&Current_Location, &Current_Rotation, Params);

}

//ProjectileRayo

void ANaveAereaJugador::StartFiringRayo()
{
	bRayoIsFiring = true;

}

void ANaveAereaJugador::StopFiringRayo()
{
	bRayoIsFiring = false;

}

void ANaveAereaJugador::FireWeaponRayo()
{
	FActorSpawnParameters Params = {};
	Params.Owner = this;

	AActor* SpawnedProjectileRayo = GetWorld()->SpawnActor(Projectile_Rayo_BP,
		&Current_Location, &Current_Rotation, Params);

}

