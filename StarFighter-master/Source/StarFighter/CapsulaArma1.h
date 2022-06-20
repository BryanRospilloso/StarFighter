// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Capsula.h"
#include "CapsulaArma1.generated.h"

class UStaticMeshComponent;

UCLASS()
class STARFIGHTER_API ACapsulaArma1 : public ACapsula
{
	GENERATED_BODY()

public:
	ACapsulaArma1();

	UPROPERTY()
		UStaticMeshComponent* CapsulaArmaMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Generar() override;

	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved,
			FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
};
