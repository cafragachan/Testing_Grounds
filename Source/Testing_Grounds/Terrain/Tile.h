// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTING_GROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Spawns different Props in BP
	UFUNCTION(BlueprintCallable, Category = "Procedural")
	void PlaceActors(TSubclassOf<AActor> ActorToSpawn, int MinNumber = 1, int MaxNumber = 1, float Radius_ = 250, float MinScale = 1, float MaxScale = 1);

	//check if Random Procedural location is available
	bool CanSpawnAtLocation(FVector Location_, float Radius_);

	//Evaluate Empty Location
	bool FindEmptyLocation(FVector& OUTTestLocation_, float Radius_);

	//Place Spawned actor 
	void PlaceActor(TSubclassOf<AActor> ActorToSpawn_, FVector Location_, float Rotation_, float Scale_);

	static FVector RandomPositionInTile();

};