#include "BTTask_ExploreCaluweYanto.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "NavigationSystem.h"

UBTTask_ExploreCaluweYanto::UBTTask_ExploreCaluweYanto()
{
	NodeName = TEXT("Explore YC");
}

EBTNodeResult::Type UBTTask_ExploreCaluweYanto::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	// Debug text reveal
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Explore task: Execute task called"));
	
	AAIController* Controller = root.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = root.GetBlackboardComponent();
	
	if (!Controller || !BlackboardComponent) // If couldnt grab one of the two. return failed and debug
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Explore task: no Controller/Blackboard"));
		return EBTNodeResult::Failed;
	}
	
	APawn* Pawn = Controller->GetPawn();
	if (!Pawn)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Explore task: no Pawn"));
		return EBTNodeResult::Failed;
	}
	
	FVector Origin = Pawn->GetActorLocation();
	FVector TargetLocation = Origin;
	bool bFound = false;
	
	UWorld* World = Controller->GetWorld();
	if (UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World)) // try getting the NAV system
	{
		FNavLocation NavLocation;
		if (NavSystem->GetRandomReachablePointInRadius(Origin, SearchRadius, NavLocation)) // Get a point in the GIVEN radius
		{
			TargetLocation = NavLocation.Location;
			bFound = true;			
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Explore task: nav not found"));
	}
	
	if (bFound)
	{
		// Dispaly information
		FString message = FString::Printf(TEXT("Explore task: going to %s (key: %s)"),
			*TargetLocation.ToString(), *TargetLocationKey.SelectedKeyName.ToString());
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f,FColor::Blue,message);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f,FColor::Orange,TEXT("Explore task: nav random pos not found"));
	}
	
	// Pass location along
	BlackboardComponent->SetValueAsVector(TargetLocationKey.SelectedKeyName, TargetLocation);
	Controller->MoveToLocation(TargetLocation); // Move the actor to target Location
		GEngine->AddOnScreenDebugMessage(-1, 5.f,FColor::Green,TEXT("Explore task: nav random pos not found"));
	
	return EBTNodeResult::Succeeded;
} 