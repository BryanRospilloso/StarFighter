// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveAerea.h"
#include "InventoryComponent.h"
#include "SlingShot.h"
#include "ClockTower.h"
#include "NaveAereaEnemiga01.h"
#include "NaveAereaJugador.generated.h"

UCLASS()
class STARFIGHTER_API ANaveAereaJugador : public ANaveAerea
{
	GENERATED_BODY()
	
	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

public:
	ANaveAereaJugador();

private:
	AClockTower* ClockTower;
	ANaveAereaEnemiga01* NaveAereaEnemiga01;

public:
	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Actor Interface

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;

	//ProyectilBala
	void FireBala();
	void FireShotBala(FVector FireDirection);

	//ProyectilBomba
	void FireBomba();
	void FireShotBomba(FVector FireDirection);

	//ProyectilMisil
	void FireMisil();
	void FireShotMisil(FVector FireDirection);

	//ProyectilRayo
	void FireRayo();
	void FireShotRayo(FVector FireDirection);

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

	//void Fire();

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	//Inventario
	UPROPERTY()
		UInventoryComponent* ShipInventory;

	UPROPERTY()
		TMap<FString, int32> ShipInfo;

	UFUNCTION()
		void TakeItem(AInventoryActor* InventoryItem);

	UFUNCTION()
		void DropItem();

	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved,
			FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION()
		void ShowInventory();

	UFUNCTION()
		void ConsumirVelocidad();

	UFUNCTION()
		void ConsumirVida();

	UFUNCTION()
		void DisminuirVelocidad();

	UFUNCTION()
		void DisminuirVida();

	UFUNCTION()
		void VisibilityOff();

	UFUNCTION()
		void VisibilityOn();

	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	/* Flag to control firing  */
	uint32 bCanFire : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	float FireForwardValue;
	float FireRightValue;

	ISlingShot* SlingShot;

public:
	//Funcion que nos permitira aumentar la vida y armadura de nuestra nave cuando recojamos un objeto

	void CollectablePickup1();

	//Funcion que nos permitira reducir la velocidad de nuestra nave

	void CollectablePickup2();

	//Set the Weapon Actor
	void SetSlingShot(AActor* SlingShotObj);

	//Fire with the SlingShot
	void Sling1();

	void CollectableCapsulaArma1();
	float Danio;

	void CollectableCapsulaEscudo1();
	float Escudo;

	void CollectableCapsulaEnergia1();
	float Energia;

	void CollectableCapsulaVida1();

	FVector CurrentLocation;

	//ANaveAereaJugador* GetPosicion() { return naveposision; }

};
