// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PoyPoyChar.generated.h"

/**
 * 
 */
UCLASS()
class GSPTECHDEMO4_API UPoyPoyChar : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "PoyPoyAnim")
		void CustomUpdateAnimation();

	UFUNCTION()
		void AnimNotify_Pickup();

	UFUNCTION()
		void AnimNotify_Throw();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyAnim")
		bool isHolding;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyAnim")
		bool isInAir;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyAnim")
		bool canMove;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyAnim")
		bool isHit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyAnim")
		bool isDead;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyAnim")
		float moveSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyAnim")
		class APawn* pawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyAnim")
		class APoyPoyCharacter* poypoyChar;

};
