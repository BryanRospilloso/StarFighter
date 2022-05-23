// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Nave.generated.h"

class UStaticMeshComponent;
//class UCapsuleComponent;

UCLASS()
class STARFIGHTER_API ANave : public APawn
{
	GENERATED_BODY()

protected:
	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ShipMeshComponent;

	//UPROPERTY(EditAnywhere)
		//UCapsuleComponent* CapsuleCollision;

public:
	// Sets default values for this pawn's properties
	ANave();

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	int32 Vida;


	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireBinding;

	UPROPERTY(EditAnywhere)
		float MaxVelocity;

	float Current_X_Velocity;
	float Current_Y_Velocity;

	FVector Current_Location;
	FRotator Current_Rotation;
	FVector New_Location;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	FORCEINLINE void SetShipMeshComponent(class UStaticMeshComponent* _ShipMeshComponent) { ShipMeshComponent = _ShipMeshComponent; }
};
