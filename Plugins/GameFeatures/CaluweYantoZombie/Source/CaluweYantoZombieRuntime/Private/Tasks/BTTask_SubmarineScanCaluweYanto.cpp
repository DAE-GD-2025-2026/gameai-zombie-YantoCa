#include "Tasks/BTTask_SubmarineScanCaluweYanto.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"

UBTTask_SubmarineScanCaluweYanto::UBTTask_SubmarineScanCaluweYanto()
{
	NodeName = TEXT("Look around 360");
	
	bNotifyTick = true;
	
	RotationSpeed = 180.f;
	TotalDegreesRotated = 0.f;
}

EBTNodeResult::Type UBTTask_SubmarineScanCaluweYanto::ExecuteTask(UBehaviorTreeComponent& root, uint8* NodeMemory)
{
	AAIController* AIController = root.GetAIOwner();
	if (!AIController || !AIController->GetPawn())
	{
		return EBTNodeResult::Failed;
	}
	
	// Reset
	TotalDegreesRotated = 0.f;
	
	// Clear focus so pathfinding doesnt work against it
	AIController->ClearFocus(EAIFocusPriority::Default);
	AIController->StopMovement();
	
	return EBTNodeResult::InProgress;
}

void UBTTask_SubmarineScanCaluweYanto::TickTask(UBehaviorTreeComponent& root, uint8* nodeMemory, float dt)
{
	Super::TickTask(root, nodeMemory, dt);
	
	AAIController* AIController = root.GetAIOwner();
	if (!AIController)
	{
		FinishLatentTask(root, EBTNodeResult::Failed);
		return;
	}
	
	APawn* Pawn = AIController->GetPawn();
	if (!Pawn)
	{
		FinishLatentTask(root, EBTNodeResult::Failed);
		return;
	}
	
	float DegreesToRotate = RotationSpeed * dt;
	
	// Rotate pawn
	FRotator currentRotation = Pawn->GetActorRotation();
	currentRotation.Yaw += DegreesToRotate;
	Pawn->SetActorRotation(currentRotation);
	
	AIController->SetControlRotation(currentRotation);
	
	TotalDegreesRotated += FMath::Abs(DegreesToRotate);
	
	if (TotalDegreesRotated >= 360.f)
	{
		FinishLatentTask(root, EBTNodeResult::Succeeded);
	}
}
