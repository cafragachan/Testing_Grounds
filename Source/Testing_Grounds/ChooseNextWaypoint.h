// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"


/**
 * 
 */
UCLASS()
class TESTING_GROUNDS_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	
private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


public:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector CurrentWaypoint;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector NextWaypointIndex;


private:

	TArray<AActor*>Waypoints;

};
