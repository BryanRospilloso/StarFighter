// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveAerea.h"
#include "InventoryComponent.h"
#include "Projectile.h"
#include "Projectile_Bala.h"
#include "Projectile_Bomba.h"
#include "Projectile_Misil.h"
#include "Projectile_Rayo.h"
#include "NaveAereaJugador.generated.h"

/**
 * 
 */
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
	
	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Actor Interface

	void MoveUp(float AxisValue);

	void MoveRight(float AxisValue);

	void Fire();
	
	/* Fire a shot in the specified direction */
	void FireShot(FVector FireDirection);

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

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
		void Test();

	UFUNCTION()
		void ConsumirVelocidad();

	UFUNCTION()
		void ConsumirVida();

	UFUNCTION()
		void DisminuirVelocidad();

	UFUNCTION()
		void DisminuirVida();

	UFUNCTION()
		void FastShoot();

	UFUNCTION()
		void SlowShoot();

	//ProjectileBala

	void FireWeaponBala();
	void StartFiringBala();
	void StopFiringBala();
	bool bBalaIsFiring;
	float FireBalaRate;
	float BalaTimeSinceLastShot;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile_Bala> Projectile_Bala_BP;

	//ProjectileBomba

	void FireWeaponBomba();
	void StartFiringBomba();
	void StopFiringBomba();
	bool bBombaIsFiring;
	float FireBombaRate;
	float BombaTimeSinceLastShot;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile_Bomba> Projectile_Bomba_BP;

	//ProjectileMisil

	void FireWeaponMisil();
	void StartFiringMisil();
	void StopFiringMisil();
	bool bMisilIsFiring;
	float FireMisilRate;
	float MisilTimeSinceLastShot;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile_Misil> Projectile_Misil_BP;

	//ProjectileRayo

	void FireWeaponRayo();
	void StartFiringRayo();
	void StopFiringRayo();
	bool bRayoIsFiring;
	float FireRayoRate;
	float RayoTimeSinceLastShot;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile_Rayo> Projectile_Rayo_BP;

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

};
