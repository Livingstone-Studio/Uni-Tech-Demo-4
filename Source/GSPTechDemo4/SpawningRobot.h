// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawningRobot.generated.h"

UCLASS()
class GSPTECHDEMO4_API ASpawningRobot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawningRobot();

	UPROPERTY(EditAnywhere, Category = "PoyPoySpawnRobot")
		TArray<class TSubclassOf<class ACratePickup>> pickups;

	UPROPERTY(EditAnywhere, Category = "PoyPoySpawnRobot")
		FVector spawnOffset;

	UPROPERTY(EditAnywhere, Category = "PoyPoySpawnRobot")
		int pickupLimit;

	UPROPERTY(EditAnywhere, Category = "PoyPoySpawnRobot")
		float timeBetweenSpawns;

	UPROPERTY(EditAnywhere, Category = "PoyPoySpawnRobot")
		float arenaSize;

	float spawnTimer;

	bool targettingDefault;
	bool active;

	FVector targetPosition;

	FVector defaultPosition;

	void TrySpawningPickup();

	void SpawnPickup();

	TArray<ACratePickup*> pickupsOnPitch;
	void RemoveFromList(ACratePickup* pickup);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
