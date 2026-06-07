#pragma once

#include  "CoreMinimal.h"
#include  "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindNextHouseCaluweYanto.generated.h"

// Make unreal class. and prefix U = UObject (garbage collected and memory managed)
UCLASS()
class  CALUWEYANTOZOMBIERUNTIME_API UBTTask_FindNextHouseCaluweYanto : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindNextHouseCaluweYanto();
	
protected:
	// override Task, inheritance
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;
	
	// Selector for target housePos (property on the node)
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FBlackboardKeySelector NextHousePositionKey;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FBlackboardKeySelector TargetLocationKey;
};