// Fill out your copyright notice in the Description page of Project Settings.


#include "EntranceDoor.h"

// Sets default values
AEntranceDoor::AEntranceDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	RDoorWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Door Wall"));
	RDoorWall->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

	LDoorWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Door Wall"));
	LDoorWall->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
	RightFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Door Frame"));
	RightFrame->AttachToComponent(RDoorWall, FAttachmentTransformRules::KeepRelativeTransform);

	RightGlass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Door Glass"));
	RightGlass->AttachToComponent(RightFrame, FAttachmentTransformRules::KeepRelativeTransform);

	RightDoorHandler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Door Handler"));
	RightDoorHandler->AttachToComponent(RightGlass, FAttachmentTransformRules::KeepRelativeTransform);

	

	LeftFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Door Frame"));
	LeftFrame->AttachToComponent(LDoorWall, FAttachmentTransformRules::KeepRelativeTransform);

	LeftGlass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Door Glass"));
	LeftGlass->AttachToComponent(LeftFrame, FAttachmentTransformRules::KeepRelativeTransform);

	LeftDoorHandler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Door Handler"));
	LeftDoorHandler->AttachToComponent(LeftGlass, FAttachmentTransformRules::KeepRelativeTransform);

	RightPhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("R Physics Constraint"));
	RightPhysicsConstraint->AttachToComponent(RightFrame, FAttachmentTransformRules::KeepRelativeTransform);

	LeftPhysicsConstraint= CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("L Physics Constraint"));
	LeftPhysicsConstraint->AttachToComponent(LeftFrame, FAttachmentTransformRules::KeepRelativeTransform);

	RightPhysicsConstraint->SetConstrainedComponents(RightFrame,NAME_None,nullptr,NAME_None);
	LeftPhysicsConstraint->SetConstrainedComponents(LeftFrame,NAME_None,nullptr,NAME_None);


}

// Called when the game starts or when spawned
void AEntranceDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEntranceDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

