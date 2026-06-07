// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HouseTrackerComponentCaluweYanto.h"
#include "Components/ActorComponent.h"
#include "Components/InverntoryComponentCaluweYanto.h"
#include "Components/ZombieTrackerComponentCaluweYanto.h"
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
	UInventoryComponentCaluweYanto* GetInventory() const { return InventoryComponent; }

	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);	
private:
	// Methods
	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;
	UPROPERTY()
	UHouseTrackerComponentCaluweYanto* HouseTrackerComponent;
	UPROPERTY()
	UInventoryComponentCaluweYanto* InventoryComponent;
	UPROPERTY()
	UZombieTrackerComponentCaluweYanto* ZombieTrackerComponent;
	UPROPERTY()
	UHealthComponent* HealthComponent;
	
	int GetItemValue(const ABaseItem& Item);
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	int previousHealth{};
	
	// Propertys
	/// Items
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FName ItemKeyName{ "Item" }; 
	
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FName ItemSeenKeyName{ "ItemSeen" }; 
	
	/// Location
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FName TargetLocationKeyName{ "TargetLocation" }; 

	/// Zombies
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FName ZombieDangerKeyName{ "IsInDanger" }; 

	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FName NearestZombieKeyName{ "NearestZombie" }; 
	
	/// Pawn Well being
	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FName NeedsHealingKeyName{ "NeedsHealing" }; 

	UPROPERTY(EditAnywhere, Category = "Blackboard");
	FName NeedsFoodKeyName{ "NeedsFood" }; 
};
