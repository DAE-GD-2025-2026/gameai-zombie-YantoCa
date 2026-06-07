#pragma once

#include  "CoreMinimal.h"
#include  "BehaviorTree/BTTaskNode.h"
#include "BTTask_SubmarineScanCaluweYanto.generated.h"

// Make unreal class. and prefix U = UObject (garbage collected and memory managed)
UCLASS()
class  CALUWEYANTOZOMBIERUNTIME_API UBTTask_SubmarineScanCaluweYanto : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SubmarineScanCaluweYanto();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& root, uint8* nodeMemory, float dt) override;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float RotationSpeed;
private:
	float TotalDegreesRotated;
};