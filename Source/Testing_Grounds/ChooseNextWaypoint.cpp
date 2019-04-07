// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Public/PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackBoardComponent = OwnerComp.GetBlackboardComponent();
	auto AIController = OwnerComp.GetAIOwner();
	auto AIPawn = AIController->GetPawn();
	auto AICharacter = Cast<APatrollingGuard>(AIPawn);
	int32 index = BlackBoardComponent->GetValueAsInt(NextWaypointIndex.SelectedKeyName);

	UE_LOG(LogTemp, Warning, TEXT("AICharacter: %s"), *AICharacter->GetName());

	if (!ensure(AIController && AICharacter)) return EBTNodeResult::Failed;

	Waypoints = AICharacter->TargetPoints;

	BlackBoardComponent->SetValueAsObject(CurrentWaypoint.SelectedKeyName, Waypoints[index]);
	BlackBoardComponent->SetValueAsInt(NextWaypointIndex.SelectedKeyName, (index + 1) % Waypoints.Num());

	return EBTNodeResult::Succeeded;
}
