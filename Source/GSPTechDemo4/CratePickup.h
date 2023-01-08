// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CratePickup.generated.h"

UCLASS()
class GSPTECHDEMO4_API ACratePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACratePickup();


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCrate")
		bool isThrown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCrate")
		bool isDestroyOnImpact;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCrate")
		bool isExplosive;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCrate")
		float timeTillExplode;

	UPROPERTY(BlueprintReadWrite, BlueprintReadWrite, Category = "PoyPoyCrate")
		class UStaticMeshComponent* box;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PoyPoyCrate")
		class TSubclassOf<class AItemPickup> drop;

	UPROPERTY(BlueprintReadWrite, BlueprintReadWrite, Category = "PoyPoyCrate")
		class UBoxComponent* collider;

	UFUNCTION()
		void OnImpact(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void SetupCollision();

	bool droppedOff;

	bool exploding;

	float explodeTimer;

	class ASpawningRobot* robot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
