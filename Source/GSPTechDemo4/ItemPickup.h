// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemPickup.generated.h"

UCLASS()
class GSPTECHDEMO4_API AItemPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPickup();

	UPROPERTY(BlueprintReadWrite, BlueprintReadWrite, Category = "PoyPoyItem")
		class UStaticMeshComponent* box;

	UPROPERTY(EditAnywhere, Category = "PoyPoyItem")
		float timeTillActive;


	UFUNCTION(BlueprintCallable)
		void SetupCollision();

	UFUNCTION()
		void OnImpact(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	float activeTimer;

	class ATree* tree;

	bool inital = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
