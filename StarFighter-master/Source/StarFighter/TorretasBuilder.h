// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TorretasBuilder.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTorretasBuilder : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STARFIGHTER_API ITorretasBuilder
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BuildSoporteTorreta() = 0;
	virtual void BuildCuerpoTorreta() = 0;
	virtual void BuildArmasTorreta() = 0;
	virtual class ATorretas* GetTorretas() = 0;

};
