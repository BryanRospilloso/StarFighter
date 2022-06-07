// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TorretasBuilder.h"
#include "TurretGunBuilder.generated.h"

UCLASS()
class STARFIGHTER_API ATurretGunBuilder : public AActor, public ITorretasBuilder
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretGunBuilder();

private:
	UPROPERTY(VisibleAnywhere, Category = "Turret Gun")
		class ATorretas* Torretas;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BuildSoporteTorreta() override;
	virtual void BuildCuerpoTorreta() override;
	virtual void BuildArmasTorreta() override;
	virtual class ATorretas* GetTorretas() override;

};
