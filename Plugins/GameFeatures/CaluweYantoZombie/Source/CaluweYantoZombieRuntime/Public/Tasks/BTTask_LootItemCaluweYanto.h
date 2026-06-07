#pragma once

#include  "CoreMinimal.h"
#include  "BehaviorTree/BTTaskNode.h"
#include "BTTask_LootItemCaluweYanto.generated.h"

// Make unreal class. and prefix U = UObject (garbage collected and memory managed)
UCLASS()
class  CALUWEYANTOZOMBIERUNTIME_API UBTTask_LootItemCaluweYanto : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_LootItemCaluweYanto();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FBlackboardKeySelector ItemSeenKeySelector;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FBlackboardKeySelector ItemKey;
};