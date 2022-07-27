// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "State.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UState : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STARFIGHTER_API IState
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//The pure virtual functions of the State
	virtual void InsertCoin() = 0;
	virtual void RejectCoin() = 0;
	virtual void PullLever() = 0;
	virtual void Payout() = 0;
	virtual void RestockDollars() = 0;
	virtual FString ToString() = 0;
	virtual void SetSlotMachine(class AOldSchoolSlotMachine* SlotMachine) = 0;
};
