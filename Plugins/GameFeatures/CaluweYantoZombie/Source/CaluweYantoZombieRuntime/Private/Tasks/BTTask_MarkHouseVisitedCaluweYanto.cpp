#include "Tasks/BTTask_MarkHouseVisitedCaluweYanto.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "Components/HouseTrackerComponentCaluweYanto.h"
#include "StudentPerceptorCaluweYanto.h"
#include "Village/House/House.h"

UBTTask_MarkHouseVisitedCaluweYanto::UBTTask_MarkHouseVisitedCaluweYanto()
{
	NodeName = TEXT("Marking This House");
}

EBTNodeResult::Type UBTTask_MarkHouseVisitedCaluweYanto::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	AAIController* Controller = root.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = root.GetBlackboardComponent();
	
	if (!BlackboardComponent || !Controller) return EBTNodeResult::Failed; 
	
	APawn* Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;
	 
	UStudentPerceptorCaluweYanto* Perceptor = Pawn->FindComponentByClass<UStudentPerceptorCaluweYanto>();
	if (!Perceptor || !Perceptor->GetHouseTracker()) return EBTNodeResult::Failed; // No perceptor or component we need
	
	UHouseTrackerComponentCaluweYanto* Tracker = Perceptor->GetHouseTracker();
	
	Tracker->MarkAsVisited(Pawn->GetActorLocation());
	
	FVector newNextHousePos = Tracker->GetNextUnvisitedHousePosition();
	bool bHasHousesLeft = !Tracker->IsHousesEmpty();
	
	BlackboardComponent->SetValueAsVector(NextHousePositionKey.SelectedKeyName, newNextHousePos);
	BlackboardComponent->SetValueAsBool(TEXT("HousesLeftToVisit"), bHasHousesLeft);
	
	return EBTNodeResult::Succeeded;
}