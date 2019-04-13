// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Testing_GroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTING_GROUNDS_API AInfiniteTerrainGameMode : public ATesting_GroundsGameMode
{
	GENERATED_BODY()

		AInfiniteTerrainGameMode();

protected:

	virtual void BeginPlay() override;

	void AddToPool(class ANavMeshBoundsVolume* NavMesh);

public:

	UFUNCTION(BlueprintCallable, Category = "Tile")
	void PopulateBoundsVolumePool();

protected:

	UPROPERTY(BlueprintReadOnly)
	class UActorPool* NavPool;

	
};
