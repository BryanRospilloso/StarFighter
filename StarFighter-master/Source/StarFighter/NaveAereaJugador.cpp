// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAereaJugador.h"
#include "Proyectil_Bala.h"
#include "Proyectil_Bomba.h"
#include "Proyectil_Misil.h"
#include "Proyectil_Rayo.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

const FName ANaveAereaJugador::MoveForwardBinding("MoveForward");
const FName ANaveAereaJugador::MoveRightBinding("MoveRight");

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
	bCanFire = true;

	FireForwardValue = 0.0f;
	FireRightValue = 0.0f;

	//Ship info
	ShipInfo.Add("Vida", 0);
	ShipInfo.Add("Velocidad", 0);
	ShipInfo.Add("RestarVida", 0);
	ShipInfo.Add("RestarVelocidad", 0);
	ShipInfo.Add("Visibility_Off", 0);
	ShipInfo.Add("Visibility_On", 0);

}

void ANaveAereaJugador::BeginPlay()
{
	Super::BeginPlay();

}

void ANaveAereaJugador::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	
	PlayerInputComponent->BindAction(TEXT("FireBala"), IE_Pressed, this, &ANaveAereaJugador::FireBala);
	PlayerInputComponent->BindAction(TEXT("FireBomba"), IE_Pressed, this, &ANaveAereaJugador::FireBomba);
	PlayerInputComponent->BindAction(TEXT("FireMisil"), IE_Pressed, this, &ANaveAereaJugador::FireMisil);
	PlayerInputComponent->BindAction(TEXT("FireRayo"), IE_Pressed, this, &ANaveAereaJugador::FireRayo);
	PlayerInputComponent->BindAction(TEXT("DropItem"), EInputEvent::IE_Pressed, this, &ANaveAereaJugador::DropItem);
	PlayerInputComponent->BindAction(TEXT("ShowInventory"), IE_Pressed, this, &ANaveAereaJugador::ShowInventory);
	PlayerInputComponent->BindAction(TEXT("ConsumirVelocidad"), IE_Pressed, this, &ANaveAereaJugador::ConsumirVelocidad);
	PlayerInputComponent->BindAction(TEXT("ConsumirVida"), IE_Pressed, this, &ANaveAereaJugador::ConsumirVida);
	PlayerInputComponent->BindAction(TEXT("DisminuirVelocidad"), IE_Pressed, this, &ANaveAereaJugador::DisminuirVelocidad);
	PlayerInputComponent->BindAction(TEXT("DisminuirVida"), IE_Pressed, this, &ANaveAereaJugador::DisminuirVida);
	PlayerInputComponent->BindAction(TEXT("VisibilityOff"), IE_Pressed, this, &ANaveAereaJugador::VisibilityOff);
	PlayerInputComponent->BindAction(TEXT("VisibilityOn"), IE_Pressed, this, &ANaveAereaJugador::VisibilityOn);

}



void ANaveAereaJugador::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

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

void ANaveAereaJugador::FireBala()
{
	bCanFire = true;

	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	FireShotBala(FireDirection);

}

void ANaveAereaJugador::FireShotBala(FVector FireDirection)
{
	if (bCanFire == true)
	{
		const FRotator FireRotation = FireDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			// spawn the projectile
			World->SpawnActor<AProyectil_Bala>(SpawnLocation, FireRotation);

		}

		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAereaJugador::ShotTimerExpired, FireRate);

		bCanFire = false;

	}

}

void ANaveAereaJugador::FireBomba()
{
	bCanFire = true;

	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	FireShotBomba(FireDirection);

}

void ANaveAereaJugador::FireShotBomba(FVector FireDirection)
{
	if (bCanFire == true)
	{
		const FRotator FireRotation = FireDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			// spawn the projectile
			World->SpawnActor<AProyectil_Bomba>(SpawnLocation, FireRotation);

		}

		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAereaJugador::ShotTimerExpired, FireRate);

		bCanFire = false;

	}

}

void ANaveAereaJugador::FireMisil()
{
	bCanFire = true;

	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	FireShotMisil(FireDirection);

}

void ANaveAereaJugador::FireShotMisil(FVector FireDirection)
{
	if (bCanFire == true)
	{
		const FRotator FireRotation = FireDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			// spawn the projectile
			World->SpawnActor<AProyectil_Misil>(SpawnLocation, FireRotation);

		}

		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAereaJugador::ShotTimerExpired, FireRate);

		bCanFire = false;

	}

}

void ANaveAereaJugador::FireRayo()
{
	bCanFire = true;

	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	FireShotRayo(FireDirection);

}

void ANaveAereaJugador::FireShotRayo(FVector FireDirection)
{
	if (bCanFire == true)
	{
		const FRotator FireRotation = FireDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			// spawn the projectile
			World->SpawnActor<AProyectil_Rayo>(SpawnLocation, FireRotation);

		}

		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAereaJugador::ShotTimerExpired, FireRate);

		bCanFire = false;

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
				MoveSpeed += 500.0f;
				
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
				MoveSpeed -= 500.0f;
				
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

void ANaveAereaJugador::VisibilityOff()
{
	FString n = "Visibility_Off";
	for (auto& pair : ShipInfo)
	{
		if (pair.Key == n)
		{
			if (pair.Value > 0)
			{
				pair.Value = pair.Value - 1;
				ShipMeshComponent->SetVisibility(false);

			}
			break;
		}
	}

}

void ANaveAereaJugador::VisibilityOn()
{
	FString n = "Visibility_On";
	for (auto& pair : ShipInfo)
	{
		if (pair.Key == n)
		{
			if (pair.Value > 0)
			{
				pair.Value = pair.Value - 1;
				ShipMeshComponent->SetVisibility(true);

			}
			break;
		}
	}

}

void ANaveAereaJugador::CollectablePickup1()
{
	MoveSpeed += 500.0f;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Velocidad del jugador aumentada %f"), MoveSpeed));

}

void ANaveAereaJugador::CollectablePickup2()
{
	this->Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("ELIMINADO")));
}
