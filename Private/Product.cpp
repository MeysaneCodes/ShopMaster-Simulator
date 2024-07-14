// Fill out your copyright notice in the Description page of Project Settings.


#include "Product.h"

// Sets default values
AProduct::AProduct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SceneComponent->SetupAttachment(RootComponent);

	//Surrounding = CreateDefaultSubobject<USceneComponent>(TEXT("Surrounding Scene"));
	//Surrounding->AttachToComponent(SceneComponent,FAttachmentTransformRules::KeepRelativeTransform);


	BoxCollision =  CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	BoxCollision->AttachToComponent(SceneComponent,FAttachmentTransformRules::KeepRelativeTransform);
	
	CardBoxSkeletalMesh =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Cardboard Box"));
	CardBoxSkeletalMesh->AttachToComponent(BoxCollision,FAttachmentTransformRules::KeepRelativeTransform);

	
	ProductPackAssigned = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Product"));
	ProductPackAssigned->AttachToComponent(BoxCollision,FAttachmentTransformRules::KeepRelativeTransform);

	ProductPackAssigned2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Product2"));
	ProductPackAssigned2->AttachToComponent(BoxCollision,FAttachmentTransformRules::KeepRelativeTransform);

	ProductPackAssigned3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Product3"));
	ProductPackAssigned3->AttachToComponent(BoxCollision,FAttachmentTransformRules::KeepRelativeTransform);

	ProductPackAssigned4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Product4"));
	ProductPackAssigned4->AttachToComponent(BoxCollision,FAttachmentTransformRules::KeepRelativeTransform);

	PickedItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chosen Item Picked"));
	PickedItem->AttachToComponent(BoxCollision,FAttachmentTransformRules::KeepRelativeTransform);



	
	ProductPackAssigned->SetSimulatePhysics(false);

    if (!Tag.IsEmpty())
    {
    	
    	this->Tags.Add("Product");
    }

	ProductDetails.Add("Name","");
	ProductDetails.Add("Description","");
	ProductDetails.Add("Price","");
	ProductDetails.Add("Amount","1");
	
}

// Called when the game starts or when spawned
void AProduct::BeginPlay()
{
	Super::BeginPlay();

	//if(ProductPackAssigned)
	ProductPackAssigned->AttachToComponent(CardBoxSkeletalMesh,FAttachmentTransformRules::KeepWorldTransform);
	//if(ProductPackAssigned2)
	ProductPackAssigned2->AttachToComponent(CardBoxSkeletalMesh,FAttachmentTransformRules::KeepWorldTransform);
	//if(ProductPackAssigned3)
	ProductPackAssigned3->AttachToComponent(CardBoxSkeletalMesh,FAttachmentTransformRules::KeepWorldTransform);
	//if(ProductPackAssigned4)
	ProductPackAssigned4->AttachToComponent(CardBoxSkeletalMesh,FAttachmentTransformRules::KeepWorldTransform);

	if(!ProductsList.IsEmpty())
	{
		for (int Index = 0; Index <= ProductsList.Num()-1; Index++)
		{
			if (ProductsList[Index])
			{
				switch (Index)
				{
				case 0:
					GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("Done"));
					ProductPackAssigned->SetStaticMesh(ProductsList[Index]);
					ProductAmount++;
					UE_LOG(LogTemp,Error,TEXT("First Product EQUIPPED"));

					break;
				case 1:
					GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("Done"));
					ProductPackAssigned2->SetStaticMesh(ProductsList[Index]);
					ProductAmount++;
					break;
				case 2:
					GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("Done"));
					ProductPackAssigned3->SetStaticMesh(ProductsList[Index]);
					ProductAmount++;
					break;
				case 3:
					GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("Done"));
					ProductPackAssigned4->SetStaticMesh(ProductsList[Index]);
					ProductAmount++;
					break;

				default:
					UE_LOG(LogTemp,Error,TEXT("Error Occured"));
					break;
				}
			}
			
		}
		//ProductPackAssigned->SetStaticMesh(ProductPack);
		
		
	}
	

	//PickedItem->SetStaticMesh(itemDefault);

}

// Called every frame
void AProduct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!this->Tags.IsEmpty())
	{
		//GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,this->Tags[0].ToString());
	}


}

