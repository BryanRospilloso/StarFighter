// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TorretasPlane.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTorretasPlane : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STARFIGHTER_API ITorretasPlane
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetSoporteTorreta(FString SoporteTorreta) = 0;
	virtual void SetCuerpoTorreta(FString CuerpoTorreta) = 0;
	virtual void SetArmasTorreta(FString ArmasTorreta) = 0;
};
