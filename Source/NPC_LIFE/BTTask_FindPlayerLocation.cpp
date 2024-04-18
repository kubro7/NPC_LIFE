// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerLocation.h"

#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Find Player Location in Nav Mesh");
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type RetVal = EBTNodeResult::Failed;

	// get player character
	if (auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		// get player location
		auto const PlayerLocation = Player->GetActorLocation();
		if (SearchRandom)
		{
			FNavLocation SelectedLocation;

			//get the navigation system and generate a random location near the player
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				// try to get a random location around the player
				if (NavSys->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, SelectedLocation))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), SelectedLocation.Location);

					//finish with success
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					RetVal = EBTNodeResult::Succeeded;
				}
			}
		}
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);

			//finish with success
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			RetVal = EBTNodeResult::Succeeded;
		}
	}
	return RetVal;
}
