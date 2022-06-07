// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TorretasPlane.h"
#include "Torretas.generated.h"

class UStaticMeshComponent;

UCLASS()
class STARFIGHTER_API ATorretas : public AActor, public ITorretasPlane
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorretas();

	UPROPERTY()
		UStaticMeshComponent* TorretaMesh;

private:
	FString SoporteTorreta;
	FString CuerpoTorreta;
	FString ArmasTorreta;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSoporteTorreta(FString mySoporteTorreta);
	void SetCuerpoTorreta(FString myCuerpoTorreta);
	void SetArmasTorreta(FString myArmasTorreta);

	void TorretasCharacteristics();

};
