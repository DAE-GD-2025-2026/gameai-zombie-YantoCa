#include "Tasks/BTTask_LookAtZombieCaluweYanto.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_LookAtZombieCaluweYanto::UBTTask_LookAtZombieCaluweYanto()
{
    NodeName = "Rotate To Nearest Zombie"; 
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_LookAtZombieCaluweYanto::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (!Controller || !BlackboardComp) return EBTNodeResult::Failed;

    AActor* Zombie = Cast<AActor>(BlackboardComp->GetValueAsObject(NearestZombieKey.SelectedKeyName));
    if (!Zombie) return EBTNodeResult::Failed;
 
    return EBTNodeResult::InProgress;
}

void UBTTask_LookAtZombieCaluweYanto::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (!Controller || !BlackboardComp)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    APawn* Pawn = Controller->GetPawn();
    AActor* Zombie = Cast<AActor>(BlackboardComp->GetValueAsObject(NearestZombieKey.SelectedKeyName));

    if (!Pawn || !Zombie)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }
 
    FVector LookAtVector = Zombie->GetActorLocation() - Pawn->GetActorLocation(); 
    LookAtVector.Z = 0.f; 
    
    FRotator TargetRotation = LookAtVector.ToOrientationRotator(); 
    FRotator CurrentRotation = Pawn->GetActorRotation();
    FRotator NewRotation = UKismetMathLibrary::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, RotationSpeed); 
    Pawn->SetActorRotation(NewRotation);
 
    if (FMath::Abs(NewRotation.Yaw - TargetRotation.Yaw) < 2.f)
    { 
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}