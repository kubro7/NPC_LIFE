// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "NpcAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "AI/Navigation/NavigationTypes.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location in Nav Mesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type retVal = EBTNodeResult::Failed;

	// get AI controller and its npc
	if (auto* const Controller = Cast<ANpcAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const Npc = Controller->GetPawn())
		{
			//obtain npc location to use as origin
			auto const Origin = Npc->GetActorLocation();

            //get the navigation system and generate a random location
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc))
				{
					if (auto* const Blackboard = Controller->GetBlackboardComponent())
					{
						Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), Loc);
					}					
				}
				
				//finish with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				retVal = EBTNodeResult::Succeeded;
			}
		}
	}
	return retVal;
}


