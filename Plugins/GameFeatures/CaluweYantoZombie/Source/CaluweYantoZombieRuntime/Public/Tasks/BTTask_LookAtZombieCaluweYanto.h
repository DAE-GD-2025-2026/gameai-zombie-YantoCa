#pragma once

#include  "CoreMinimal.h"
#include  "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookAtZombieCaluweYanto.generated.h"

// Make unreal class. and prefix U = UObject (garbage collected and memory managed)
UCLASS()
class  CALUWEYANTOZOMBIERUNTIME_API UBTTask_LookAtZombieCaluweYanto : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_LookAtZombieCaluweYanto();
	
protected:
	// override Task, inheritance
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
		
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FBlackboardKeySelector NearestZombieKey;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float RotationSpeed{5.f};
	
};