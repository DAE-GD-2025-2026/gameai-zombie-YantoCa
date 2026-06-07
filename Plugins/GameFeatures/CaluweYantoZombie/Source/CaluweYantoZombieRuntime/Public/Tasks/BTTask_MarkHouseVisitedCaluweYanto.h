#pragma once

#include  "CoreMinimal.h"
#include  "BehaviorTree/BTTaskNode.h"
#include "BTTask_MarkHouseVisitedCaluweYanto.generated.h"

// Make unreal class. and prefix U = UObject (garbage collected and memory managed)
UCLASS()
class  CALUWEYANTOZOMBIERUNTIME_API UBTTask_MarkHouseVisitedCaluweYanto : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MarkHouseVisitedCaluweYanto();
	
protected:
	// override Task, inheritance
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FBlackboardKeySelector NextHousePositionKey;
};