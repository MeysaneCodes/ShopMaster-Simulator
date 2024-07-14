// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveableActor.h"

// Sets default values
AMoveableActor::AMoveableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	Crate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crate Box"));

	
	RootComponent = SceneComponent;
	//BoxCollision->SetupAttachment(SceneComponent);
	Crate->AttachToComponent(SceneComponent,FAttachmentTransformRules::KeepRelativeTransform);
	
	

}

// Called when the game starts or when spawned
void AMoveableActor::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AMoveableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMoveableActor::print()
{
	GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black,TEXT("YOS"));

}

