// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptorCaluweYanto.h"

#include "AIController.h"
#include "HeadMountedDisplayTypes.h"
#include "IDetailTreeNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/HouseTrackerComponentCaluweYanto.h"

#include "Village/House/House.h"
#include "Items/BaseItem.h"
#include "Zombies/BaseZombie.h"

UStudentPerceptorCaluweYanto::UStudentPerceptorCaluweYanto()
{
	PrimaryComponentTick.bCanEverTick = true; 
}

void UStudentPerceptorCaluweYanto::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptorCaluweYanto::OnPerceptionUpdated);
	}
	
	BlackboardComponent = Cast<AAIController>(Cast<APawn>(GetOwner())->GetController())->GetBlackboardComponent();
	BlackboardComponent->SetValueAsObject("Perceptor", this);
	
	HouseTrackerComponent = GetOwner()->FindComponentByClass<UHouseTrackerComponentCaluweYanto>();
	if (!HouseTrackerComponent) // Check if we have the Component
	{
		// Create the component and attach it
		HouseTrackerComponent = NewObject<UHouseTrackerComponentCaluweYanto>(GetOwner(), UHouseTrackerComponentCaluweYanto::StaticClass(), TEXT("RuntimeHouseTrackerComponent"));
		if(HouseTrackerComponent)
		{
			HouseTrackerComponent->RegisterComponent();
		}
	}
	
	InventoryComponent = GetOwner()->FindComponentByClass<UInventoryComponentCaluweYanto>();
	if (!InventoryComponent) // Check if we have the Component
	{
		// Create the component and attach it
		InventoryComponent = NewObject<UInventoryComponentCaluweYanto>(GetOwner(), UInventoryComponentCaluweYanto::StaticClass(), TEXT("RuntimeInventoryTrackerComponent"));
		if(InventoryComponent)
		{
			InventoryComponent->RegisterComponent();
		}
	}
	
	ZombieTrackerComponent = GetOwner()->FindComponentByClass<UZombieTrackerComponentCaluweYanto>();
	if (!ZombieTrackerComponent) // Check if we have the Component
	{
		// Create the component and attach it
		ZombieTrackerComponent = NewObject<UZombieTrackerComponentCaluweYanto>(GetOwner(), UZombieTrackerComponentCaluweYanto::StaticClass(), TEXT("RuntimeZombieTrackerComponent"));
		if(ZombieTrackerComponent)
		{
			ZombieTrackerComponent->RegisterComponent();
		}
	}
}

void UStudentPerceptorCaluweYanto::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!BlackboardComponent || !HouseTrackerComponent)
	{
		GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Red,TEXT("Missing Important Component"));
		return;
	}
	
	if (!Stimulus.WasSuccessfullySensed() || Stimulus.IsExpired()) return; // early stop if it really sensed something
	 
	// Houses
	if (auto SensedHouse = Cast<AHouse>(Actor)) // is house then
	{ 
		if (HouseTrackerComponent->ContainsHouse(*SensedHouse)) // return early, if already in list
		{
			GEngine->AddOnScreenDebugMessage(6, 2.f, FColor::Yellow,TEXT("Already seen the house"));
			return;
		}
		
		HouseTrackerComponent->AddHouse(SensedHouse); // Add to the list for memory
		GEngine->AddOnScreenDebugMessage(6, 2.f, FColor::Green,TEXT("Added New House"));
		
		// Set true if there are *Unvisited* Houses still left over
		BlackboardComponent->SetValueAsBool("HousesLeftToVisit", !HouseTrackerComponent->IsHousesEmpty());
		
		// Set Next house to *Visit* 
		FVector TargetPos = HouseTrackerComponent->GetNextUnvisitedHousePosition();
		BlackboardComponent->SetValueAsVector(TEXT("NextHouseLocation"), TargetPos);	
	}
	
	// Items
	if ( auto SensedItem = Cast<ABaseItem>(Actor) )
	{
		if (GetItemValue(*SensedItem) > 0) // Ignore useless items
		{
			// Try grabbing the currentItem on blackboard
			if (ABaseItem* currentBBItem = Cast<ABaseItem>(BlackboardComponent->GetValueAsObject(ItemKeyName)))
			{ 
				// Check which one is more important
				if (GetItemValue(*currentBBItem) > GetItemValue(*SensedItem))
				{
					SensedItem = currentBBItem;
				}
			}
		
			// Set currentItem on blackboard
			BlackboardComponent->SetValueAsObject(ItemKeyName, SensedItem);
			BlackboardComponent->SetValueAsBool(ItemSeenKeyName, true);
		
			GEngine->AddOnScreenDebugMessage(6, 2.f, FColor::Green,TEXT("Seen Item"));
			BlackboardComponent->SetValueAsVector(TargetLocationKeyName, SensedItem->GetActorLocation() );
		}
	}
	
	// Zombies
	if (auto SensedZombie = Cast<ABaseZombie>(Actor))
	{
		ZombieTrackerComponent->AddZombie(SensedZombie); // Add to the list
		
		// Update locations
		ZombieTrackerComponent->UpdateNearestZombies(GetOwner()->GetActorLocation());
		
		BlackboardComponent->SetValueAsObject(NearestZombieKeyName, ZombieTrackerComponent->GetNearestZombie());
		BlackboardComponent->SetValueAsBool(ZombieDangerKeyName, ZombieTrackerComponent->IsInDanger(GetOwner()->GetActorLocation()));
	}
	
	
	GEngine->AddOnScreenDebugMessage(5, 2.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something! %s"), *Actor->GetName()));
}

void UStudentPerceptorCaluweYanto::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!BlackboardComponent || !ZombieTrackerComponent || !HouseTrackerComponent) return; // Cancel early
	//BlackboardComponent->SetValueAsBool(ZombieDangerKeyName, false);

	FVector PlayerLocation = GetOwner()->GetActorLocation();
	
	
	// Update Zombies
	ZombieTrackerComponent->UpdateNearestZombies(PlayerLocation);
	BlackboardComponent->SetValueAsObject(NearestZombieKeyName, ZombieTrackerComponent->GetNearestZombie());
	
	bool bIsCurrentlyInDanger = ZombieTrackerComponent->IsInDanger(PlayerLocation);
	bool bWasInDangerLastFrame = BlackboardComponent->GetValueAsBool(ZombieDangerKeyName);

	// 4. Pas het blackboard ALLEEN aan als de status daadwerkelijk omslaat!
	if (bIsCurrentlyInDanger != bWasInDangerLastFrame)
	{
		BlackboardComponent->SetValueAsBool(ZombieDangerKeyName, bIsCurrentlyInDanger);
	}
	
	
	//BlackboardComponent->SetValueAsBool(ZombieDangerKeyName, ZombieTrackerComponent->IsInDanger(PlayerLocation));
}

int UStudentPerceptorCaluweYanto::GetItemValue(const ABaseItem& Item)
{
	switch (Item.GetItemType())
	{
		case EItemType::Shotgun:
		case EItemType::Pistol:
			return 3;
		case EItemType::Medkit:
			return 2;
		case  EItemType::Food:
			return 1;
		default: // Anything else 0
			return 0; 
	}
}
