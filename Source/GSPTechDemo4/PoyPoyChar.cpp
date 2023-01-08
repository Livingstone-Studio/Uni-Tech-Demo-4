// Fill out your copyright notice in the Description page of Project Settings.


#include "PoyPoyCharacter.h"
#include "PoyPoyChar.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPoyPoyChar::NativeInitializeAnimation() 
{
	canMove = true;
	isHit = false;
	isDead = false;
	
	if (pawn == nullptr) 
	{
		pawn = TryGetPawnOwner();
	}

	if (pawn && poypoyChar == nullptr) 
	{
		poypoyChar = Cast<APoyPoyCharacter>(pawn);
	}
}

void UPoyPoyChar::CustomUpdateAnimation()
{
	if (pawn == nullptr)
	{
		pawn = TryGetPawnOwner();
	}

	if (pawn && poypoyChar == nullptr)
	{
		poypoyChar = Cast<APoyPoyCharacter>(pawn);
	}

	if (pawn) 
	{
		if (poypoyChar) 
		{
			canMove = poypoyChar->canMove;
			isHolding = poypoyChar->isHolding;
			isHit = poypoyChar->isHit;
			isDead = poypoyChar->isDead;
		}

		FVector speed = pawn->GetVelocity();
		FVector lateralSpeed = FVector(speed.X, speed.Y, 0);

		if (!canMove) lateralSpeed = FVector::ZeroVector;

		moveSpeed = lateralSpeed.Size();

		isInAir = pawn->GetMovementComponent()->IsFalling();
	}
}

void UPoyPoyChar::AnimNotify_Pickup()
{
	if (poypoyChar)
	{
		poypoyChar->Pickup();
	}
}

void UPoyPoyChar::AnimNotify_Throw()
{
	if (poypoyChar)
	{
		poypoyChar->Throw(40);
	}
}
