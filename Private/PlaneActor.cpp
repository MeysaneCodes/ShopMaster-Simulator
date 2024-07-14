// Fill out your copyright notice in the Description page of Project Settings.

#include "PlaneActor.h"
#include "Components/CapsuleComponent.h"


// Sets default values
APlaneActor::APlaneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	this->RootComponent = Capsule;

	MovingCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	MovingCube->SetupAttachment(RootComponent);


	timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("My Timeline"));

	
	

	
	
}

void APlaneActor::TimelineUpdate(float Value)
{
	UStaticMeshComponent* CubeReference = Cast <UStaticMeshComponent> (this->RootComponent->GetChildComponent(0));

	
	FVector currenctlocation = CubeReference->GetComponentLocation();
	float newlocation = currenctlocation.X + Value;
	currenctlocation.X = newlocation;
	
	MovingCube->SetWorldLocation(currenctlocation);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, ("Moving") + CubeReference->GetComponentLocation().ToString());

}

void APlaneActor::FinishEvent() 
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, ("Finished"));
}

// Called when the game s�tarts or when spawned
void APlaneActor::BeginPlay()
{
	Super::BeginPlay();

	//MovingCube->SetRelativeScale3D(FVector(1, 1, 1));
	
	//FTransform CubeTransform;
	//this->AddComponent("MovingCube", false, CubeTransform, MovingCube);
	//MovingCube->SetRelativeLocation(FVector(0, 0, 0));

	CurrentNumber = 10.0f;

	FOnTimelineFloat bindingUpdateFunktion;
	FOnTimelineEvent onFinished;
	
	bindingUpdateFunktion.BindUFunction(this,TEXT("TimelineUpdate"));

	onFinished.BindUFunction(this,TEXT("FinishEvent"));
	

	if(timeline)
	{
		timeline->AddInterpFloat(floatCurve,bindingUpdateFunktion);
		timeline->SetTimelineFinishedFunc(onFinished);
	}
	

}

// Called every frame
void APlaneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (timeline)
	{
		if(timeline->IsPlaying())
		{

			timeline->PlayFromStart();
		}
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, this->RootComponent->GetRelativeLocation().ToString());
	UStaticMeshComponent* CubeReference = Cast <UStaticMeshComponent> (this->RootComponent->GetChildComponent(0));

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, CubeReference->GetComponentLocation().ToString());


	if(!MovingCube){ 
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Valid"));

		//UE_LOG(LogTemp, Warning, TEXT("Location is %s"), *MovingCube->GetComponentLocation().ToString());
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, MovingCube->GetComponentLocation().ToString());
	}
	
	
	

}

