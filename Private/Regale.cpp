// Fill out your copyright notice in the Description page of Project Settings.


#include "Regale.h"

// Sets default values
ARegale::ARegale()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	Regale = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Regale"));
	Regale->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	Floor->AttachToComponent(Regale, FAttachmentTransformRules::KeepRelativeTransform);

	Floor2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor 2"));
	Floor2->AttachToComponent(Regale, FAttachmentTransformRules::KeepRelativeTransform);

	Floor3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor 3"));
	Floor3->AttachToComponent(Regale, FAttachmentTransformRules::KeepRelativeTransform);

	Floor4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor 4"));
	Floor4->AttachToComponent(Regale, FAttachmentTransformRules::KeepRelativeTransform);

	ProductBox1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Product Box 1 "));
	ProductBox2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Product Box 2 "));
	ProductBox3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Product Box 3 "));
	ProductBox4 = CreateDefaultSubobject<UBoxComponent>(TEXT("Product Box"));


	ProductBox1->AttachToComponent(Floor, FAttachmentTransformRules::KeepRelativeTransform);
	ProductBox2->AttachToComponent(Floor2, FAttachmentTransformRules::KeepRelativeTransform);
	ProductBox3->AttachToComponent(Floor3, FAttachmentTransformRules::KeepRelativeTransform);
	ProductBox4->AttachToComponent(Floor4, FAttachmentTransformRules::KeepRelativeTransform);



	SceneComponent->SetRelativeScale3D(FVector(0.29f,0.34f,0.36f));
}

// Called when the game starts or when spawned
void ARegale::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AmainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ProductBox1->OnComponentBeginOverlap.AddDynamic(this,&ARegale::OnRegalOneBeginOverlap);
	ProductBox1->OnComponentEndOverlap.AddDynamic(this,&ARegale::OnRegalEndOverlap);

	
	ProductBox2->OnComponentBeginOverlap.AddDynamic(this,&ARegale::OnRegalBeginOverlap2);
	ProductBox2->OnComponentEndOverlap.AddDynamic(this,&ARegale::OnRegalEndOverlap2);

	ProductBox3->OnComponentBeginOverlap.AddDynamic(this,&ARegale::OnRegalBeginOverlap3);
	ProductBox3->OnComponentEndOverlap.AddDynamic(this,&ARegale::OnRegalEndOverlap3);

	//TODO FIX THIS
	//ProductBox4->OnComponentBeginOverlap.AddDynamic(this,&ARegale::OnRegalBeginOverlap4);
	//ProductBox4->OnComponentEndOverlap.AddDynamic(this,&ARegale::OnRegalEndOverlap4);


	//Initialise Sockets
	for (TArray<FName> Sockets = Floor->GetAllSocketNames(); auto AssignedNames: Sockets)
	{
		ProductStorageLocation.Add(AssignedNames,false);
	}

	for (TArray<FName> Sockets = Floor2->GetAllSocketNames(); auto AssignedNames: Sockets)
	{
		ProductStorageLocation2.Add(AssignedNames,false);
	}

	for (TArray<FName> Sockets = Floor3->GetAllSocketNames(); auto AssignedNames: Sockets)
	{
		ProductStorageLocation3.Add(AssignedNames,false);
	}

	for (TArray<FName> Sockets = Floor4->GetAllSocketNames(); auto AssignedNames: Sockets)
	{
		ProductStorageLocation4.Add(AssignedNames,false);
	}

	
	
}

void ARegale::PutOnProductOnRegal(TArray<AActor*> OutOverlappedActor, UStaticMeshComponent* Regal)

{
	if (!OutOverlappedActor.IsEmpty())
	{
		TArray<AProduct> ProductsToMove;

		if (!Character->bIsGrabbing)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Runs"));

			for (auto A: OutOverlappedActor)
			{
				AProduct* Product = Cast<AProduct>(A);
				
				if (Product && !bIsSearchingForProductRunning)
				{
					if (!Product->bIsPlaced)
					{

						bIsSearchingForProductRunning = true;

						if (!ProductStorageLocation["0"])
						{
							GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("false"));

						}


						for (auto  id :ProductStorageLocation)
						{


							if (!id.Value && Character && !Character->bIsGrabbing)
							{

								GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("FOUND"));

								GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, id.Key.ToString());
								Product->ProductPackAssigned->SetWorldLocation(Regal->GetSocketLocation(id.Key));
								Product->ProductPackAssigned->SetWorldRotation(Regal->GetSocketRotation(id.Key));
								
								//Product->AssignedProduct->AttachToComponent(Product->Surrounding,FAttachmentTransformRules::KeepRelativeTransform);
								ProductStorageLocation[id.Key] = true;
								//	Product->Tags.Add("Placed");
							//	Product->bIsPlaced = true;
								Product->ProductPackAssigned->SetSimulatePhysics(false);
								Product->ProductPackAssigned->WakeRigidBody();
								break;
							}
						}
						bIsSearchingForProductRunning = false;
					}
				}
			}
		}
		
	}
}

void ARegale::OnRegalOneBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProduct* Product = Cast<AProduct>(OtherActor);
	if (Product)
	{
		bIsOverlapping1 = true;
	}
}

void ARegale::OnRegalEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProduct* Product = Cast<AProduct>(OtherActor);
	if (Product)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Stop"));
		bIsOverlapping1 = false;
	}
}

void ARegale::OnRegalBeginOverlap2(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AProduct* Product = Cast<AProduct>(OtherActor);
	if (Product)
	{
		bIsOverlapping2 = true;
	}
}

void ARegale::OnRegalEndOverlap2(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProduct* Product = Cast<AProduct>(OtherActor);
	if (Product)
	{
		bIsOverlapping2 = false;
	}
}

void ARegale::OnRegalBeginOverlap3(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProduct* Product = Cast<AProduct>(OtherActor);
	if (Product)
	{
		bIsOverlapping3 = true;
	}
}

void ARegale::OnRegalEndOverlap3(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProduct* Product = Cast<AProduct>(OtherActor);
	if (Product)
	{

		bIsOverlapping3 = false;
	}
}

void ARegale::OnRegalBeginOverlap4(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProduct* Product = Cast<AProduct>(OtherActor);
	if (Product)
	{
		bIsOverlapping4 = true;
	}
}

void ARegale::OnRegalEndOverlap4(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProduct* Product = Cast<AProduct>(OtherActor);
	if (Product)
	{
		bIsOverlapping4 = false;
	}
}

// Called every frame
void ARegale::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> OverlappedActors;
	TArray<AActor*> OverlappedActors2;
	TArray<AActor*> OverlappedActors3;
	TArray<AActor*> OverlappedActors4;

	if (bIsOverlapping1)
	{
		ProductBox1->GetOverlappingActors(OverlappedActors,ProductFilter);
		PutOnProductOnRegal(OverlappedActors,Floor);
	}

	if (bIsOverlapping2)
	{
		ProductBox2->GetOverlappingActors(OverlappedActors2,ProductFilter);
		PutOnProductOnRegal(OverlappedActors2,Floor2);
	}

	if (bIsOverlapping3)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Found one"));
		ProductBox3->GetOverlappingActors(OverlappedActors3,ProductFilter);
		PutOnProductOnRegal(OverlappedActors3,Floor3);
	}

	if (bIsOverlapping4)
	{
		ProductBox4->GetOverlappingActors(OverlappedActors4,ProductFilter);
		PutOnProductOnRegal(OverlappedActors4,Floor4);
	}
	
	//ProductBox1->GetOverlappingActors(OverlappedActors,ProductFilter);
	//ProductBox2->GetOverlappingActors(OverlappedActors2,ProductFilter);
	//ProductBox3->GetOverlappingActors(OverlappedActors3,ProductFilter);
	//ProductBox4->GetOverlappingActors(OverlappedActors4,ProductFilter);

	if (!OverlappedActors.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Found one"));
		
	}
	//PutProductOnRegale(OverlappedActors,Floor);
	//PutProductOnRegale(OverlappedActors2,Floor2);
	//PutProductOnRegale(OverlappedActors3,Floor3);
	//PutProductOnRegale(OverlappedActors4,Floor4);

	

}

