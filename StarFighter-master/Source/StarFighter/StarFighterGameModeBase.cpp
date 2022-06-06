// Copyright Epic Games, Inc. All Rights Reserved.


#include "StarFighterGameModeBase.h"
#include "NaveNodrizaAereaEnemiga.h"

void AStarFighterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//auto ne = SpawnNave<ANaveTerrestreEnemiga01>();
	//UE_LOG(LogTemp, Warning, TEXT("Dentro de BeginPlay en GameModeBase"));
	GetWorld()->SpawnActor<ANaveNodrizaAereaEnemiga>(FVector(-10.0f, -9.0f, 300.0f), FRotator(0.0f, 90.0f, 0.0f));
	GetWorld()->SpawnActor<ANaveNodrizaAereaEnemiga>(FVector(-20.0f, -9.0f, 200.0f), FRotator(0.0f, 180.0f, 0.0f));
}

AStarFighterGameModeBase::AStarFighterGameModeBase()
{
	/*UE_LOG(LogTemp, Warning, TEXT("Dentro de constructor en GameModeBase"));
	GetWorld()->SpawnActor<ANaveTerrestreEnemiga01>(FVector::ZeroVector, FRotator::ZeroRotator);*/

	//SpawnNave<ANaveTerrestreEnemiga01>();

}
