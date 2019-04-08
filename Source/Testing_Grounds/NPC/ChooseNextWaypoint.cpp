// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Public/PatrollingComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackBoardComponent = OwnerComp.GetBlackboardComponent();
	auto AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	int32 index = BlackBoardComponent->GetValueAsInt(NextWaypointIndex.SelectedKeyName);
	auto PatrollingComp = AIPawn->FindComponentByClass<UPatrollingComponent>();

	if (!ensure(PatrollingComp)) return EBTNodeResult::Failed;

	Waypoints = PatrollingComp->GetTargetPoints();

	if (!ensure(Waypoints.Num() > 0)) return EBTNodeResult::Failed;

	BlackBoardComponent->SetValueAsObject(CurrentWaypoint.SelectedKeyName, Waypoints[index]);
	BlackBoardComponent->SetValueAsInt(NextWaypointIndex.SelectedKeyName, (index + 1) % Waypoints.Num());

	return EBTNodeResult::Succeeded;
}
