// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptorCaluweYanto.h"


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
}

void UStudentPerceptorCaluweYanto::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something!")));
}
