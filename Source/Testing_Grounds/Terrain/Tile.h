// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

/**
 * Spawn Elements in defines location, rotation, scale
 */
USTRUCT()
struct FSpawnTransform
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};

/**
 * Generates Random settings for spawning actors in scene
 */
USTRUCT(BlueprintType)
struct FRandomSpawn
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(BlueprintReadWrite)
	int MinNumber = 1;

	UPROPERTY(BlueprintReadWrite)
	int MaxNumber = 1;

	UPROPERTY(BlueprintReadWrite)
	float Radius = 250;

	UPROPERTY(BlueprintReadWrite)
	float MinScale = 1;

	UPROPERTY(BlueprintReadWrite)
	float MaxScale = 1;
};



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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Spawns different Props in BP
	UFUNCTION(BlueprintCallable, Category = "Procedural")
	void PlaceActors(TSubclassOf<AActor> ActorToSpawn, FRandomSpawn RandomSpawn);

	//Spawns different Props in BP
	UFUNCTION(BlueprintCallable, Category = "Procedural")
	void PlaceAIGuards(TSubclassOf<APawn> ActorToSpawn, FRandomSpawn RandomSpawn);

	//check if Random Procedural location is available
	bool CanSpawnAtLocation(FVector Location_, float Radius_);

	//Evaluate Empty Location
	bool FindEmptyLocation(FVector& OUTTestLocation_, float Radius_);

	//Place Spawned actor 
	AActor* PlaceActor(TSubclassOf<AActor> ActorToSpawn_, FSpawnTransform SpawnTransform_);

	static FVector RandomPositionInTile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	class UActorPool* NavPool;


	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetPool(UActorPool* NavPool_);


private:

	AActor* NavMesh;

	TArray<FSpawnTransform> SetRandomSpawnTransform(FRandomSpawn RandomSpawn);

	/*template<class T>
	void PlaceActors(TSubclassOf<AActor> ActorToSpawn, FRandomSpawn RandomSpawn);*/

};