// Fill out your copyright notice in the Description page of Project Settings.


#include "CashDesk.h"

#include "mainCharacter.h"
#include "Product.h"

// Sets default values
ACashDesk::ACashDesk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	DirectionArrow->AttachToComponent(SceneComponent,FAttachmentTransformRules::KeepRelativeTransform);

	CashDesk = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cashdesk"));
	CashDesk->AttachToComponent(SceneComponent,FAttachmentTransformRules::KeepRelativeTransform);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(CashDesk,FAttachmentTransformRules::KeepRelativeTransform);

	Computer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Computer"));
	Computer->AttachToComponent(CashDesk,FAttachmentTransformRules::KeepRelativeTransform);

	ScreenComputer = CreateDefaultSubobject<UWidgetComponent>(TEXT("Screen"));
	ScreenComputer->AttachToComponent(Computer,FAttachmentTransformRules::KeepRelativeTransform);


	CashDesk->SetRelativeScale3D(FVector(0.5f,0.5f,0.5f));
	Computer->SetRelativeScale3D(FVector(0.5f,0.5f,0.5f));

	ConveyorBelt = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Conveyor Belt"));
	ConveyorBelt->AttachToComponent(CashDesk,FAttachmentTransformRules::KeepRelativeTransform);

	OverlappingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Detector"));
	OverlappingBox->AttachToComponent(ConveyorBelt,FAttachmentTransformRules::KeepRelativeTransform);

	StopSensor = CreateDefaultSubobject<UBoxComponent>(TEXT("Sensor Box"));
	StopSensor->AttachToComponent(ConveyorBelt,FAttachmentTransformRules::KeepRelativeTransform);

	ScannerDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("Scanner"));
	ScannerDetector->AttachToComponent(CashDesk,FAttachmentTransformRules::KeepRelativeTransform);


	//Slot Collision
	Slot1CollisionBox1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Slot Box 1"));
	Slot1CollisionBox1->AttachToComponent(CashDesk,FAttachmentTransformRules::SnapToTargetNotIncludingScale,"0");
	
	Slot1CollisionBox2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Slot Box 2"));
	Slot1CollisionBox2->AttachToComponent(CashDesk,FAttachmentTransformRules::SnapToTargetNotIncludingScale,"1");

	Slot1CollisionBox3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Slot Box 3"));
	Slot1CollisionBox3->AttachToComponent(CashDesk,FAttachmentTransformRules::SnapToTargetNotIncludingScale,"2");

}

// Called when the game starts or when spawned
void ACashDesk::BeginPlay()
{
	Super::BeginPlay();

	 mainCh = Cast<AmainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ScannerDetector->OnComponentBeginOverlap.AddDynamic(this,&ACashDesk::OnBeginOverlap);



	//TODO Must be saved during the game
	ConditionList.Add(TEXT("0"),false);
	ConditionList.Add(TEXT("1"),false);
	ConditionList.Add(TEXT("2"),false);
	ConditionList.Add(TEXT("3"),false);
	ConditionList.Add(TEXT("4"),false);
	ConditionList.Add(TEXT("5"),false);
	ConditionList.Add(TEXT("6"),false);

	ScreenWidget = Cast<UUS_ComputerScreenWidget>(ScreenComputer->GetUserWidgetObject());

	Slot1CollisionBox1->SetWorldLocation(CashDesk->GetSocketTransform("0").GetLocation());
	Slot1CollisionBox2->SetWorldLocation(CashDesk->GetSocketTransform("1").GetLocation());
	Slot1CollisionBox3->SetWorldLocation(CashDesk->GetSocketTransform("2").GetLocation());

	/*
	auto Product = GetWorld()->SpawnActor<AProduct>(ProductClassRef,Slot1CollisionBox1->GetComponentLocation(),Slot1CollisionBox1->GetComponentRotation());
	Product->SceneComponent->SetVisibility(false);
	Product->BoxCollision->SetVisibility(false);
	Product->CardBoxSkeletalMesh->SetVisibility(false);
	Product->PickedItem->SetVisibility(true);
	if(Product && Product->PickedItem)
	{

		auto s = Product->PickedItem->SetStaticMesh(Product->itemDefault);

		if (s)
		{
			GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("xy"));

		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("no"));

		}
	}
	*/



	
}


void ACashDesk::AddtoScannedProducts()
{
	
}

void ACashDesk::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AProduct* Product = Cast<AProduct>(OtherActor))
	{
		if(!Product->bIsScanned)
		GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("TIIIIT"));
		if (mainCh)
		{
			//mainCh->bIsGrabbing = false;
			//mainCh->PhysicHandler->ReleaseComponent();
			mainCh->ReleaseProduct();
			Product->BoxCollision->SetSimulatePhysics(false);


			

			for (auto const i :ConditionList)
			{
				if (!i.Value)
				{
					GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black,TEXT("OVS"));
					//Product->BoxCollision->SetWorldLocationAndRotation(CashDesk->GetSocketLocation(i.Key),FRotator(0,0,0));


					Product->PickedItem->SetWorldLocationAndRotation(CashDesk->GetSocketLocation(i.Key),FRotator(0,0,0));
					//Product->BoxCollision->AttachToComponent(CashDesk,FAttachmentTransformRules::SnapToTargetNotIncludingScale,i.Key);
					ConditionList[i.Key] = true;
					Product->bIsScanned = true;
					break;
				}
			}


			


			

		}
	}
}

 void ACashDesk::ConveyorBeltDetector(float inSpeed) 
{
	TArray<AActor*> OutOverlappedActors;
	TArray<AActor*> OutSensorOverlappedActors;

	OverlappingBox->GetOverlappingActors(OutOverlappedActors,ProductClassRef);



	//check if we hit Sensor
	StopSensor->GetOverlappingActors(OutSensorOverlappedActors,ProductClassRef);
	if (!OutSensorOverlappedActors.IsEmpty())
	{
		//GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,OutOverlappedActors[0]->GetName());

		for (auto DetectedActors : OutSensorOverlappedActors)
		{
			if (DetectedActors->ActorHasTag("ItemProduct"))
			{
				//GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("NOW"));
				UE_LOG(LogTemp,Display,TEXT("Sensor detects an Object!"))
				shouldMove = false;
			}
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("Wo"));

		shouldMove = true;
	}
	

	
	if (!OutOverlappedActors.IsEmpty())
	{

		for (auto a : OutOverlappedActors)
		{
			if (a != this && a->ActorHasTag("ItemProduct"))
			{

				if (shouldMove)
				{
					//GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("Wo"));
					if (a->ActorHasTag("ItemProduct"))
					{
						inSpeed = Speed;
						a->AddActorWorldOffset( DirectionArrow->GetForwardVector() * inSpeed * GetWorld()->GetDeltaSeconds() );
					}
				}
				
			}
		}
	}
	
}

// Called every frame
void ACashDesk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ConveyorBeltDetector(Speed);
	
	//UUS_ComputerScreenWidget Computer* = Cast<UUS_ComputerScreenWidget>(ScreenComputer->GetWidgetClass());
	//Computer->GetParent()->a
}

