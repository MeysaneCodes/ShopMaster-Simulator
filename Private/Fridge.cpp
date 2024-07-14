// Fill out your copyright notice in the Description page of Project Settings.


#include "Fridge.h"
#include "mainCharacter.h"
#include "PriceTag.h"
#include "Kismet/KismetStringLibrary.h" // Include this header if necessary



// Sets default values
AFridge::AFridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	Fridge = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fridge"));
	Fridge->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);


	Floor1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor 1"));
	Floor1->AttachToComponent(Fridge, FAttachmentTransformRules::KeepRelativeTransform);

	Floor2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor 2"));
	Floor2->AttachToComponent(Fridge, FAttachmentTransformRules::KeepRelativeTransform);

	Floor3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor 3"));
	Floor3->AttachToComponent(Fridge, FAttachmentTransformRules::KeepRelativeTransform);

	SceneComponent1 = CreateDefaultSubobject<USceneComponent>(TEXT("SceneDoor1"));
	SceneComponent1->AttachToComponent(Fridge, FAttachmentTransformRules::KeepRelativeTransform);
	
	DoorFridge1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFridge1"));
	DoorFridge1->AttachToComponent(SceneComponent1, FAttachmentTransformRules::KeepRelativeTransform);


	SceneComponent2 = CreateDefaultSubobject<USceneComponent>(TEXT("SceneDoor2"));
	SceneComponent2->AttachToComponent(Fridge, FAttachmentTransformRules::KeepRelativeTransform);
	
	DoorFridge2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFridge2"));
	DoorFridge2->AttachToComponent(SceneComponent2, FAttachmentTransformRules::KeepRelativeTransform);

	
	SceneComponent3 = CreateDefaultSubobject<USceneComponent>(TEXT("SceneDoor3"));
	SceneComponent3->AttachToComponent(Fridge, FAttachmentTransformRules::KeepRelativeTransform);
	
	DoorFridge3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFridge3"));
	DoorFridge3->AttachToComponent(SceneComponent3, FAttachmentTransformRules::KeepRelativeTransform);

	SceneComponent->SetRelativeScale3D(FVector(0.2f,0.2f,0.2f));
	//SceneComponent->SetWorldScale3D(FVector(0.3f,0.3f,0.3f));

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	DoorOpener1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlapping Box 1 "));
	DoorOpener2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlapping Box 2 "));
	DoorOpener3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlapping Box 3 "));

	DoorOpener1->AttachToComponent(SceneComponent1, FAttachmentTransformRules::KeepRelativeTransform);
	DoorOpener2->AttachToComponent(SceneComponent2, FAttachmentTransformRules::KeepRelativeTransform);
	DoorOpener3->AttachToComponent(SceneComponent3, FAttachmentTransformRules::KeepRelativeTransform);

	//Product Detection

	ProductBox1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Product Box 1 "));
	ProductBox2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Product Box 2 "));
	ProductBox3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Product Box 3 "));

	ProductBox1->AttachToComponent(Floor1, FAttachmentTransformRules::KeepRelativeTransform);
	ProductBox2->AttachToComponent(Floor2, FAttachmentTransformRules::KeepRelativeTransform);
	ProductBox3->AttachToComponent(Floor3, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AFridge::BeginPlay()
{
	Super::BeginPlay();

	FString FnametoString = "0";
		int toNumber =	UKismetStringLibrary::Conv_StringToInt(FnametoString);
	
	//TrackCurve.BindDynamic(this, &AFridge::UpdateDoorRotation);
	DoorOpener1->OnComponentHit.AddDynamic(this, &AFridge::AFridge::onComponentHitFirst);
	ProductBox1->OnComponentBeginOverlap.AddDynamic(this, &AFridge::AFridge::OnBoxOneBeginOverlap);
	Character = Cast<AmainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (CurveFloat)
	{
	//TimelineComponent->AddInterpFloat(CurveFloat,TrackCurve);
	///	if (TimelineComponent != nullptr)
		//{
			//TimelineComponent->Play();
	//	}
	}

	//Initialise Sockets
	 Sockets = Floor1->GetAllSocketNames();
	


	for (int Index = 0; Index<=Sockets.Num()-15;Index++)
	{
		ProductStorageLocation.Add(Sockets[Index],false);
		//PricePerProduct1.Add(GetWorld()->SpawnActor<APriceTag>(PriceTagRefrence,Floor1->GetSocketLocation(Sockets[14+Index]),FRotator(0.0f,-90.0f,0.0f)),nullptr);

		//PricePerProduct1.Add(CarriedProduct->ProductPackAssigned,);
		
	}
	ProductFloor1.SetNum(ProductStorageLocation.Num());

	 Sockets2 = Floor2->GetAllSocketNames();
	for (int Index = 0; Index<=Sockets.Num()-15;Index++)
	{
		ProductStorageLocation2.Add(Sockets[Index],false);
		//PricePerProduct2.Add(GetWorld()->SpawnActor<APriceTag>(PriceTagRefrence,Floor1->GetSocketLocation(Sockets[14+Index]),FRotator(0.0f,-90.0f,0.0f)),nullptr);

	}
	ProductFloor2.SetNum(ProductStorageLocation2.Num());

	 Sockets3 = Floor3->GetAllSocketNames();
	for (int Index = 0; Index<=Sockets.Num()-15;Index++)
	{
		ProductStorageLocation3.Add(Sockets[Index],false);
	//	PricePerProduct3.Add(GetWorld()->SpawnActor<APriceTag>(PriceTagRefrence,Floor1->GetSocketLocation(Sockets[14+Index]),FRotator(0.0f,-90.0f,0.0f)),nullptr);

	}
	ProductFloor3.SetNum(ProductStorageLocation3.Num());


	
	/*
	for (TArray<FName> Sockets = Floor1->GetAllSocketNames(); auto AssignedNames: Sockets)
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

	*/
	
}

void AFridge::UpdateDoorRotation(float Value)
{
	SceneComponent1->SetRelativeRotation(FRotator(0.0f,Value,0.0));
}

void AFridge::onComponentHitSecond(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
}

void AFridge::onComponentHitThird(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
}

void AFridge::OnBoxOneBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProduct* Product = Cast<AProduct>(OtherActor);
	if (Product)
	{
		UE_LOG(LogTemp,Warning,TEXT("OVER"));
	//	Product->Surrounding->SetWorldLocation(Fridge->GetSocketLocation("0"));
	}
}

/*
void AFridge::PutProductOnFridge(TArray<AActor*> OutOverlappedActor, UStaticMeshComponent* Floor)
{
	if (!OutOverlappedActor.IsEmpty())
	{
		TArray<AProduct> ProductsToMove;
		
		TArray<UStaticMeshComponent*> AvailableProductsOnBox;
		//CHECK AVAILABLE PRODUCTS ON BOX
		for (auto DetectedBox: OutOverlappedActor)
		{
			//BOX
			AProduct* Box = Cast<AProduct>(DetectedBox);
			for (auto  id :ProductStorageLocation)
			{
				if (!id.Value)
				{
					if (Box)
					{
						if (!Box->ProductsList.IsEmpty())
						{
							for (int Index = 0; Index <= Box->ProductsList.Max()-1; Index++)
							{
								if (Box->ProductsList[Box->ProductsList.Max()-1])
								{
									switch (Box->ProductsList.Max()-1)
									{
									case 0:
										Box->ProductPackAssigned->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
										Box->ProductPackAssigned->SetWorldLocation(Floor->GetSocketLocation(id.Key));
										Box->ProductPackAssigned->SetWorldRotation(FRotator(0.0f,180.0f,0.0f));
										ProductStorageLocation[id.Key] = true;
										Box->ProductPackAssigned->SetSimulatePhysics(false);
										Box->ProductPackAssigned->WakeRigidBody();
										break;
									case 1:
										Box->ProductPackAssigned->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
										Box->ProductPackAssigned->SetWorldLocation(Floor->GetSocketLocation(id.Key));
										Box->ProductPackAssigned->SetWorldRotation(FRotator(0.0f,180.0f,0.0f));
										ProductStorageLocation[id.Key] = true;
										Box->ProductPackAssigned->SetSimulatePhysics(false);
										Box->ProductPackAssigned->WakeRigidBody();
										break;

									case 2:
										Box->ProductPackAssigned->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
										Box->ProductPackAssigned->SetWorldLocation(Floor->GetSocketLocation(id.Key));
										Box->ProductPackAssigned->SetWorldRotation(FRotator(0.0f,180.0f,0.0f));
										ProductStorageLocation[id.Key] = true;
										Box->ProductPackAssigned->SetSimulatePhysics(false);
										Box->ProductPackAssigned->WakeRigidBody();
										break;

									case 3:
										Box->ProductPackAssigned->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
										Box->ProductPackAssigned->SetWorldLocation(Floor->GetSocketLocation(id.Key));
										Box->ProductPackAssigned->SetWorldRotation(FRotator(0.0f,180.0f,0.0f));
										ProductStorageLocation[id.Key] = true;
										Box->ProductPackAssigned->SetSimulatePhysics(false);
										Box->ProductPackAssigned->WakeRigidBody();
										break;
								
									}
								}
							}
						}
				
					}
				}
			}
			

		}

		
	}
}


*/

void AFridge::SetFloorStorageLocation(AProduct* CarriedProduct, TMap<FName,bool>& ProductStorage, UStaticMeshComponent* PutInFloor)
{

	for (auto  id :ProductStorage)
			{
				GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, "+" + id.Key.ToString());

				if (!id.Value)
				{
						if (!CarriedProduct->ProductsList.IsEmpty())
						{
							
							
							for (int Indexs = 0; Indexs <= CarriedProduct->ProductAmount-1; Indexs++)
							{
									//c++;
								//GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, FString::FromInt(CarriedProduct->ProductAmount));

								switch (CarriedProduct->ProductAmount-1)
								{
								case 0:
									{

										if (PutInFloor==Floor1)
										{
											AddPriceToProduct(CarriedProduct->ProductPackAssigned,CarriedProduct,PricePerProduct1,ProductFloor1,id.Key.ToString(),PutInFloor,ProductStorage);
										}
										else if (PutInFloor==Floor2)
										{
											AddPriceToProduct(CarriedProduct->ProductPackAssigned,CarriedProduct,PricePerProduct2,ProductFloor2,id.Key.ToString(),PutInFloor,ProductStorage);


										}else if (PutInFloor==Floor3)
										{
											AddPriceToProduct(CarriedProduct->ProductPackAssigned,CarriedProduct,PricePerProduct3,ProductFloor3,id.Key.ToString(),PutInFloor,ProductStorage);
										}
										
										break;
									}
								case 1:
									{
										if (PutInFloor==Floor1)
										{
											AddPriceToProduct(CarriedProduct->ProductPackAssigned2,CarriedProduct,PricePerProduct1,ProductFloor1,id.Key.ToString(),PutInFloor,ProductStorage);

										}
										else if (PutInFloor==Floor2)
										{
											AddPriceToProduct(CarriedProduct->ProductPackAssigned2,CarriedProduct,PricePerProduct2,ProductFloor2,id.Key.ToString(),PutInFloor,ProductStorage);

										}else if (PutInFloor==Floor3)
										{
											AddPriceToProduct(CarriedProduct->ProductPackAssigned2,CarriedProduct,PricePerProduct3,ProductFloor3,id.Key.ToString(),PutInFloor,ProductStorage);
										}
									break;
									}

									case 2:
									{

										if (PutInFloor==Floor1)
										{
											AddPriceToProduct(CarriedProduct->ProductPackAssigned3,CarriedProduct,PricePerProduct1,ProductFloor1,id.Key.ToString(),PutInFloor,ProductStorage);
										}
										else if (PutInFloor==Floor2)
										{
											AddPriceToProduct(CarriedProduct->ProductPackAssigned3,CarriedProduct,PricePerProduct2,ProductFloor2,id.Key.ToString(),PutInFloor,ProductStorage);

										}else if (PutInFloor==Floor3)
										{
											AddPriceToProduct(CarriedProduct->ProductPackAssigned3,CarriedProduct,PricePerProduct3,ProductFloor3,id.Key.ToString(),PutInFloor,ProductStorage);
										}
										break;
									}

									case 3:
									{

										if (PutInFloor==Floor1)
										{
											
											AddPriceToProduct(CarriedProduct->ProductPackAssigned4,CarriedProduct,PricePerProduct1,ProductFloor1,id.Key.ToString(),PutInFloor,ProductStorage);

										}
										else if (PutInFloor==Floor2)
										{
											AddPriceToProduct(CarriedProduct->ProductPackAssigned4,CarriedProduct,PricePerProduct2,ProductFloor2,id.Key.ToString(),PutInFloor,ProductStorage);

										}else if (PutInFloor==Floor3)
										{
									
											AddPriceToProduct(CarriedProduct->ProductPackAssigned4,CarriedProduct,PricePerProduct3,ProductFloor3,id.Key.ToString(),PutInFloor,ProductStorage);

										}
										break;
									}

									default:
										GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, "Default");

									}
								for (auto PTag: PricePerProduct1)
								{
									GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, "Hi");
									
								}
								break;
							}
							break;
						}
				
					
				}
			}
}

int AFridge::ConvertStringToInt(const FString& str)
{
	return UKismetStringLibrary::Conv_StringToInt(str);
}


void AFridge::onComponentHitFirst(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                  FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, OtherActor->GetClass()->GetName());
}


void AFridge::Delay()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("PO PO"));
	RunAmount = 0;
	bIsRunning = false;
}

void AFridge::AddPriceToProduct(UStaticMeshComponent* &ProductPack,AProduct* &InCarriedProduct, TMap<UStaticMeshComponent*,APriceTag*> &PricePerProduct,TArray<UStaticMeshComponent*> &ProductFloor,FString const& IDKey, const UStaticMeshComponent*  InPutFloor,TMap<FName,bool>& InProductStorage)
{
	ProductPack->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	ProductPack->SetWorldLocation(InPutFloor->GetSocketLocation(FName(IDKey)));
	ProductPack->SetWorldRotation(FRotator(0.0f,Fridge->GetComponentRotation().Yaw + 90.0f,0.0f));
	InProductStorage[FName(IDKey)] = true;
	ProductPack->SetSimulatePhysics(false);
	ProductPack->WakeRigidBody();
	
	//GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, "2");
	InCarriedProduct->ProductAmount--;

	
	auto PriceTag = GetWorld()->SpawnActor<APriceTag>(PriceTagRefrence,InPutFloor->GetSocketLocation((Sockets[ConvertStringToInt(IDKey)+14])),FRotator(0.0f,-90.0f,0.0f));
	PricePerProduct.Add(ProductPack,PriceTag);
	ProductFloor[ConvertStringToInt(IDKey)] = ProductPack;
	
	PriceTag->ProductName = InCarriedProduct->ProductName;
	PriceTag->Price = InCarriedProduct->Price;

	InCarriedProduct->bIsPlaced = true;
}

// Called every frame
void AFridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	ProductBox1->GetOverlappingActors(OverlappedActors);
	ProductBox2->GetOverlappingActors(OverlappedActors2);
	ProductBox3->GetOverlappingActors(OverlappedActors3);

	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::LeftMouseButton))
	{
		
		if (!OverlappedActors.IsEmpty()  || !OverlappedActors2.IsEmpty() || !OverlappedActors3.IsEmpty())
		{
			if ( !bIsRunning && RunAmount == 0)
			{
				FTimerHandle TimerHandle;
				RunAmount = 1;
				bIsRunning = true;
				GetWorldTimerManager().SetTimer(TimerHandle,this,&AFridge::Delay,0.5f,false);
			}
		}
	}
	
	//PutProductOnFridge(OverlappedActors,Floor1);
	//PutProductOnFridge(OverlappedActors2,Floor2);
	//PutProductOnFridge(OverlappedActors3,Floor3);
	

}

void AFridge::OpenDoor()
{
	
}

void AFridge::CloseDoor()
{
	
}

