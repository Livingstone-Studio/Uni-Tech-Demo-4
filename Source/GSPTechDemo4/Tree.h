// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tree.generated.h"

UCLASS()
class GSPTECHDEMO4_API ATree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATree();

	UPROPERTY(BlueprintReadWrite, BlueprintReadWrite, Category = "Tree")
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = "Tree")
		class TSubclassOf<class AItemPickup> heart;

	UPROPERTY(EditAnywhere, Category = "Tree")
		float maxRegenTime;

	void Remove(class AItemPickup* item);

	float regenTimer;

	class AItemPickup* spawnPositionOnePickup;

	class AItemPickup* spawnPositionTwoPickup;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
