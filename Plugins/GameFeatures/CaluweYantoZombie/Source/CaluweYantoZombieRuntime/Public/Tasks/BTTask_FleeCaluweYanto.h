#pragma once

#include  "CoreMinimal.h"
#include  "BehaviorTree/BTTaskNode.h"
#include "BTTask_FleeCaluweYanto.generated.h"

// Make unreal class. and prefix U = UObject (garbage collected and memory managed)
UCLASS()
class  CALUWEYANTOZOMBIERUNTIME_API UBTTask_FleeCaluweYanto : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FleeCaluweYanto();
	
protected:
	// override Task, inheritance
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;

		
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FBlackboardKeySelector NearestZombieKey;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FBlackboardKeySelector TargetLocationKey;
	
	UPROPERTY(EditAnywhere, Category = "Search")
	float FleeStrength{1500.f};
	
};