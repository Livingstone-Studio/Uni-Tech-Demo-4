// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PoyPoyCharacter.generated.h"

UCLASS()
class GSPTECHDEMO4_API APoyPoyCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	APoyPoyCharacter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCharacter")
		bool isHit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCharacter")
		bool isDead;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCharacter")
		bool isHolding;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCharacter")
		bool isJumping;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCharacter")
		float maxNoMoveTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCharacter")
		float maxHitTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCharacter")
		bool canMove;

	UPROPERTY(BlueprintReadWrite, BlueprintReadWrite, Category = "PoyPoyCharacter")
		class USphereComponent* pickupCollider;

	UPROPERTY(EditAnywhere, Category = "PoyPoyCharacter")
		class TSubclassOf<class ACratePickup> bomb;

	UPROPERTY(BlueprintReadWrite, BlueprintReadWrite, Category = "PoyPoyCharacter")
		class ACratePickup* heldPickup;

	UPROPERTY(BlueprintReadWrite, BlueprintReadWrite, Category = "PoyPoyCharacter")
		class ACratePickup* highlightedPickup;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCharacter")
		int maxHealth;

	UFUNCTION(BlueprintCallable)
		void SetupCollider();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCharacter")
	int health;

	float hitTimer;
	
	float noMoveTimer;

	void MoveForward(float value);

	void MoveHorizontal(float value);

	void JumpCheck();

	void TryPickup();

	UFUNCTION()
	void CheckOverlapForPickups(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void RemoveOverlappingPickups(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void PoyPoyTakeDamage(int amount);

	void Throw(float strength);

	void Pickup();

	void SpawnPickupInHand(TSubclassOf<class ACratePickup> pickup);

	void Hit(FVector velocity);

	void Power();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
