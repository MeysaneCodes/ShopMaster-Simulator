// Fill out your copyright notice in the Description page of Project Settings.


#include "CardboardBox.h"

// Sets default values
ACardboardBox::ACardboardBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SceneComponent->SetupAttachment(RootComponent);

	Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object"));
	Object->AttachToComponent(SceneComponent,FAttachmentTransformRules::KeepRelativeTransform);

	CardBoxSkeletalMesh =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Cardboard Box"));
	CardBoxSkeletalMesh->AttachToComponent(SceneComponent,FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ACardboardBox::BeginPlay()
{
	Super::BeginPlay();

	//TODO MAKE LOGIC TO SEE IF THIS STAYS CARD OR PACK DURING THE GAME
	Object->SetStaticMesh(CardBox);

	if (!Tag.IsEmpty())
	{
    	
		this->Tags.Add(FName(Tag));
	}
}

// Called every frame
void ACardboardBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

