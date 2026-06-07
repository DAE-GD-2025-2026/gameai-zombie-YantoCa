// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HouseTrackerComponentCaluweYanto.h"
#include "Components/ActorComponent.h"
#include "Components/InverntoryComponentCaluweYanto.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"  

#include "StudentPerceptorCaluweYanto.generated.h"
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CALUWEYANTOZOMBIERUNTIME_API UStudentPerceptorCaluweYanto : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Methods
	UStudentPerceptorCaluweYanto();
	
	virtual void BeginPlay() override;
	UHouseTrackerComponentCaluweYanto* GetHouseTracker() const { return HouseTrackerComponent; }
	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
private:
	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;
	UPROPERTY()
	UHouseTrackerComponentCaluweYanto* HouseTrackerComponent;
	UPROPERTY()
	UInventoryComponentCaluweYanto* InventoryComponent;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FName ItemKeyName{ "Item" };
};
