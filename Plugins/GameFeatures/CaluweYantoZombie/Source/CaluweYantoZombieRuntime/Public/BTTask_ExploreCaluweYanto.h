#pragma once

#include  "CoreMinimal.h"
#include  "BehaviorTree/BTTaskNode.h"
#include "BTTask_ExploreCaluweYanto.generated.h"

// Make unreal class. and prefix U = UObject (garbage collected and memory managed)
UCLASS()
class  CALUWEYANTOZOMBIERUNTIME_API UBTTask_ExploreCaluweYanto : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ExploreCaluweYanto();
	
protected:
	// override Task, inheritance
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;
	
	// Selector for target Pos (property on the node)
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FBlackboardKeySelector TargetLocationKey;
	
	// Radius for search.
	UPROPERTY(EditAnywhere, Category = "Search")
	float SearchRadius{1500.f};
	
	// UProperty is like [SerializeField] from Unity but then for Unreal
	// the value below is revealed with said name above.
};