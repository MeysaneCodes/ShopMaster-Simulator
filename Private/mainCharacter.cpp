// Fill out your copyright notice in the Description page of Project Settings.


#include "mainCharacter.h"
#include "BoxControll.h"
#include "CashDesk.h"
#include "Fridge.h"
#include "GameFramework/SpringArmComponent.h"
#include "Main_AnimInstance.h"
#include "Product.h"
#include "Components/ArrowComponent.h"
#include "Evaluation/Blending/MovieSceneBlendType.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AmainCharacter::AmainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetMesh(), TEXT("head"));
	
	ProductSlot = CreateDefaultSubobject<UBoxComponent>(TEXT("Product Spawn Slot"));
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Box"));
	//CrateBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OC Spawn"));

	PhysicHandler = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Handler"));
	
	
	//SpringArmComponent->SetupAttachment(GetMesh());
	//CameraComponent->AttachToComponent(SpringArmComponent,FAttachmentTransformRules::KeepRelativeTransform);
	//SpringArmComponent->bEnableCameraLag = true;
	//SpringArmComponent->bUsePawnControlRotation = true;

	OverlapBox->SetupAttachment(GetMesh());
	//CrateBox->SetupAttachment(GetMesh());

	OverlapBox->OnComponentBeginOverlap.AddDynamic(this,&AmainCharacter::onBeginOverlap);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this,&AmainCharacter::OnEndOverlap);

	ProductSlot->AttachToComponent(GetArrowComponent(),FAttachmentTransformRules::KeepRelativeTransform);

	InteractionWidget = CreateDefaultSubobject<UWidgetInteractionComponent>("Interaction Widget");
	InteractionWidget->AttachToComponent(CameraComponent,FAttachmentTransformRules::KeepRelativeTransform);

}

void AmainCharacter::MoveForward(float AxisValue)
{
	if (AnimInstanceRef && AxisValue == 0.0f)
	{
		AnimInstanceRef->isRunning = false;

	}
	if (AnimInstanceRef && AxisValue > 0.0f)
	{
		if (!AnimInstanceRef->isRunning)
		{
			AnimInstanceRef->isRunning = true;
			AnimInstanceRef->isJumping = false;
		//	GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("Forward"));
		}
		
		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		SkeletalMeshComponentRef->SetRelativeRotation(FRotator(SkeletalMeshComponentRef->GetRelativeRotation().Pitch,
			-90.f,
			SkeletalMeshComponentRef->GetRelativeRotation().Roll)
			);
		
		AddMovementInput(Direction, AxisValue);
		//Set Character Animation to running
	}

	//AnimInstanceRef->isRunning = false;

	
	

	
	
}
void AmainCharacter::TurnAround()
{
	if (AnimInstanceRef)
	{
		AnimInstanceRef->isTurning = false;
		SkeletalMeshComponentRef->SetRelativeRotation(FRotator(SkeletalMeshComponentRef->GetRelativeRotation().Pitch,
		90.f,
		SkeletalMeshComponentRef->GetRelativeRotation().Roll)
				);
	}
	
}

void AmainCharacter::MoveBackward(float AxisValue)
{

	if (AxisValue < 0.0f)
	{
		//if (AnimInstanceRef)
	//	{
	//		AnimInstanceRef->isJumping = false;

		//}

		
		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);


		//check if already turned
		//if (SkeletalMeshComponentRef->GetRelativeRotation().Yaw <= 89.0f)
		{
			//play turn animation
		//	if (AnimInstanceRef && !AnimInstanceRef->isTurning)
			//{
			//	AnimInstanceRef->isTurning = true;
			//	FTimerHandle TimerHandle;
			//	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &AmainCharacter::TurnAround,1.8f,false);
			}
			
		}
		
		
		//	if (SkeletalMeshComponentRef->GetRelativeRotation().Yaw != 90.0f && !AnimInstanceRef->isRunning && !AnimInstanceRef->isTurning  )
			//{
			//	AnimInstanceRef->isRunning = true;
				//AddMovementInput(Direction, AxisValue);

				//	GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("Forward"));
			}
		
		
		
	

	//AnimInstanceRef->isRunning = false;



void AmainCharacter::MoveRight(float AxisValue)
{
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction,AxisValue);
	}
	
}

void AmainCharacter::TimerCallBack()
{
	Jump();
}

void AmainCharacter::CallJump()
{
	if (AnimInstanceRef)
	{
		AnimInstanceRef->isRunning = false;
		AnimInstanceRef->isJumping = true;
		GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, TEXT("Jump Called"));
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &AmainCharacter::TimerCallBack,0.90f,false);
	}
	
}

void AmainCharacter::ToggleCarry()
{
	
		if(SkeletalMeshComponentRef->GetAnimInstance() != nullptr)
		{
			if (!isCarrying)
			{
				SkeletalMeshComponentRef->GetAnimInstance()->Montage_Play(CarryAnimation);
				isCarrying = true;
			}
			else
			{
				SkeletalMeshComponentRef->GetAnimInstance()->Montage_Stop(0.8f,CarryAnimation);
				isCarrying = false;
			}

		}
	
	
//	PlayAnimMontage(CarryAnimation);

}

void AmainCharacter::OnRightMouseClick()
{

	//Release Grabbed Object
	if (Product)
	{
		UBoxControll* BoxControll = Cast<UBoxControll>(Product->CardBoxSkeletalMesh->GetAnimInstance());
		if (BoxControll)
		{
			if (!BoxControll->bIsOpen)
			{
				BoxControll->bIsOpen = true;
			}
		}
	}

	ReleaseProduct();
	//TODO DISPLACED IN Release PRODUCT ; PENDING DELETE ///////////////////////

	/*
	if (bIsGrabbing && !bIsClearingGoods)
	{
		GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, TEXT("HOLDING NOT"));
		bIsGrabbing = false;
		PhysicHandler->ReleaseComponent();
		if (Product)
		{
			Product->BoxCollision->AttachToComponent(Product->SceneComponent,FAttachmentTransformRules::KeepWorldTransform);
			Product->CardBoxSkeletalMesh->AttachToComponent(Product->BoxCollision,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Product->BoxCollision->SetSimulatePhysics(true);
			
			//Product->CardBoxSkeletalMesh->Play(false);
			//Product->CardBoxSkeletalMesh->PlayAnimation(Product->OpenBox,false);
		}
		if (CardboardBox)
		{
			CardboardBox->Object->SetSimulatePhysics(true);
		}
		//	Product->AssignedProduct->AttachToComponent(Product->Surrounding,FAttachmentTransformRules::SnapToTargetNotIncludingScale);


		return;
	}
	*/
}

void AmainCharacter::OnLeftMouseClick()
{

	//InteractionWidget->PressKey(EKeys::LeftMouseButton);
	InteractionWidget->PressPointerKey(EKeys::LeftMouseButton);
	InteractionWidget->ReleasePointerKey(EKeys::LeftMouseButton);

	
	//Grab Component
	//PUT COMPONENT ON FRIDGE -- GIVE PERMISSION TO THE FRIDGE
	
	FHitResult OutHit;
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + (CameraComponent->GetForwardVector() * GrabRange);
	FCollisionQueryParams QueryParams = FCollisionQueryParams(TEXT("CollisionQuery"),true,this);
	QueryParams.bTraceComplex = true;
	GetWorld()->LineTraceSingleByChannel(OutHit,Start,End,ECC_Visibility,QueryParams);
	DrawDebugLine(GetWorld(),Start,End,FColor::Blue,true,1.0);
	//DrawDebugPoint(GetWorld(),OutHit.ImpactPoint,5.0f,FColor::Red,false,1.0f);
	
	if (OutHit.bBlockingHit)
	{

		//-------------------------------------------Fridge Door Control--------------------------------------------------------//


		//Check if that´s Fridge Door
		AFridge* FridgeRef;
		
		FridgeRef = Cast<AFridge>(OutHit.GetActor());

		if (FridgeRef)
		{
			GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("YO"));

		}

		if (FridgeRef && !OutHit.Component->ComponentTags.IsEmpty())
		{
			OpenFridgeDoor(OutHit,FridgeRef,OutHit.Component->ComponentTags[0]);
		}

		//----------------------------------------------------------------------------------------------------------------------//

		

		//-------------------------------------------GRABING OBJECT--------------------------------------------------------//
		//Check if Product
		GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,OutHit.GetActor()->GetName());
		GrabProduct(OutHit);
		//------------------------------------------------------------------------------------------------------------------//


		

		
		//TODO DISPLACED IN GRAB PRODUCT ; PENDING DELETE ///////////////////////
		//CARRY BOX
		/*
		if (Cast<AProduct>(OutHit.GetActor()))
		{
			Product = Cast<AProduct>(OutHit.GetActor());

			if (Product->bIsPlaced)
			{
				//SPAWN ACTOR ON TABLE
			}
		//	GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, TEXT("Block"));
			GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, OutHit.GetActor()->GetName());
			Product->BoxCollision->WakeRigidBody();
			Product->BoxCollision->SetSimulatePhysics(false);
			Product->BoxCollision->WakeRigidBody();
		//	Product->bIsPlaced = false;
			bIsGrabbing = true;
			GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("TOGGLE"));

			PhysicHandler->GrabComponentAtLocationWithRotation(OutHit.GetComponent(),TEXT("CarrySocket"),OutHit.GetComponent()->GetComponentLocation(),FRotator(0,0,0));

			//GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, PhysicHandler->GetGrabbedComponent()->GetName());


				//PhysicHandler->bRotationConstrained = true;
			
			
			
		}
		*/



		//---------------------------------Putting Object on Fridge---------------------------//


		StoreProductFridge(OutHit,FridgeRef);


		
		//TODO DISPLACED IN StoreProductFridge Method ; PENDING DELETE ///////////////////////

		//Detection Box
		/*
		if (Cast<UBoxComponent>(OutHit.Component))
		{
			//UBoxComponent* detectedBox = Cast<UBoxComponent>(OutHit.Component);

			if (bIsGrabbing && FridgeRef)
			{
				GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, OutHit.Component->GetAttachParent()->GetName());

				if (Product)
				{
					UStaticMeshComponent* DesignedObject = Cast<UStaticMeshComponent>(OutHit.Component->GetAttachParent());
					if (DesignedObject)
					{
						if (OutHit.Component->ComponentHasTag("0"))
						{
							FridgeRef->SetFloorStorageLocation(Product,FridgeRef->ProductStorageLocation,FridgeRef->Floor1);
						
						}

						else if (OutHit.Component->ComponentHasTag("1"))
						{
							FridgeRef->SetFloorStorageLocation(Product,FridgeRef->ProductStorageLocation2,FridgeRef->Floor2);

						
						}

						else if (OutHit.Component->ComponentHasTag("2"))
						{
							FridgeRef->SetFloorStorageLocation(Product,FridgeRef->ProductStorageLocation3,FridgeRef->Floor3);
						
						}

						
					}
					
					//FridgeRef->PutProductOnFridge(Product,FridgeRef->Floor1);
					//GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, "Valid2");
					//Product->ProductPackAssigned->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
					//Product->ProductPackAssigned->SetWorldLocation(FridgeRef->Floor1->GetSocketLocation("0"));
					//Product->ProductPackAssigned->SetWorldRotation(FRotator(0.0f,180.0f,0.0f));
					//FridgeRef->ProductStorageLocation["0"] = true;
					//Product->ProductPackAssigned->SetSimulatePhysics(false);
					//Product->ProductPackAssigned->WakeRigidBody();
				}
				
			}
			
		}
		*/

		//---------------------------------Putting Object on Fridge---------------------------//




		

		//check if CardboadBox

		/*
		CardboardBox = Cast<ACardboardBox>(OutHit.GetActor());

		if (CardboardBox)
		{
			GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, TEXT("Block"));
			GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, OutHit.GetActor()->GetName());
			CardboardBox->Object->WakeRigidBody();
			CardboardBox->Object->SetSimulatePhysics(false);
			CardboardBox->Object->WakeRigidBody();
			CardboardBox->bIsCardPlaced = false;
			bIsGrabbing = true;
			PhysicHandler->GrabComponentAtLocationWithRotation(OutHit.GetComponent(),TEXT("CarrySocket"),OutHit.GetComponent()->GetComponentLocation(),FRotator(0,0,0));

			
			//GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, PhysicHandler->GetGrabbedComponent()->GetName());


			//PhysicHandler->bRotationConstrained = true;
			
			
			
		}

*/

		
		
		
	}

	
	if(SkeletalMeshComponentRef->GetAnimInstance() != nullptr)
	{
		if (!isCarrying)
		{
			SkeletalMeshComponentRef->GetAnimInstance()->Montage_Play(GrabAnimation);
			isCarrying = true;
		}
		else
		{
			SkeletalMeshComponentRef->GetAnimInstance()->Montage_Stop(0.8f,GrabAnimation);
			isCarrying = false;
		}

	}
}

// Called when the game starts or when spawned
void AmainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//ProductSlot->SetRelativeLocation(FVector(0,0,0));

	//Settings
	isCarrying = false;

	//Getting Ref from Main_AnimInstance Class
	if (SkeletalMeshComponentRef != nullptr)
	{
		AnimInstanceRef =  Cast<UMain_AnimInstance>(SkeletalMeshComponentRef->GetAnimInstance());
		
	
		
		if(AnimInstanceRef != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, AnimInstanceRef->testString);
			
		}
	}

	 PlayerController = Cast<APlayerController>(GetController());


}


// Called every frame
void AmainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TestFridg)
	{
		GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black,TEXT("run"));
	}

	if (bIsGrabbing)
	{
		FVector Start = CameraComponent->GetComponentLocation();
			
		FVector End = Start + (CameraComponent->GetForwardVector() * 80);
		//PhysicHandler->GetGrabbedComponent()->SetWorldLocationAndRotation(End,GetActorRotation());

		if(Product && Product->ActorHasTag("ItemProduct"))
		{
			//GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black,TEXT("FFFS"));
			Product->BoxCollision->SetWorldLocationAndRotation(End,FRotator(GetActorRotation().Pitch,GetActorRotation().Yaw +90.0f,GetActorRotation().Roll));
			//Product->PickedItem->SetWorldLocationAndRotation(End,FRotator(GetActorRotation().Pitch,GetActorRotation().Yaw +90.0f,GetActorRotation().Roll));
			return;
		}
		if (Product)
		{
			Product->BoxCollision->SetWorldLocationAndRotation(ProductSlot->GetComponentLocation(),FRotator(GetActorRotation().Pitch,GetActorRotation().Yaw +90.0f,GetActorRotation().Roll));
		}

		if (CardboardBox)
		{
			//GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black,TEXT("run"));
			CardboardBox->Object->SetWorldLocationAndRotation(End,GetActorRotation());
		}
		
	}
	else
	{
		if (Product)
		{
			Product->CardBoxSkeletalMesh->SetWorldLocation(Product->BoxCollision->GetComponentLocation());
		}
	}


	if (GetCharacterMovement () != nullptr)
	{
		if(!GetCharacterMovement()->IsFalling())
		{
			if (AnimInstanceRef != nullptr)
			{
				//AnimInstanceRef->isJumping = false;

			}
		}
		
	}

	double ActorDirection = GetActorForwardVector().X;
	

	//ActorDirection.Normalize();

	//When going back, check if actor is already turned back with scale pitch, if not then turn if yes then start running

	
	//GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black,TEXT("Value is %s"), *ActorDirection.ToString());

	
	

	
	

}

// Called to bind functionality to input
void AmainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AmainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Backward", this, &AmainCharacter::MoveBackward);
	

	PlayerInputComponent->BindAxis("Right", this, &AmainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Left", this, &AmainCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &AmainCharacter::CallJump);
	PlayerInputComponent->BindAction("Jump",IE_Released, this, &AmainCharacter::StopJumping);

	PlayerInputComponent->BindAction("Carry",IE_Pressed, this, &AmainCharacter::ToggleCarry);

	PlayerInputComponent->BindAction("Trigger",IE_Pressed, this, &AmainCharacter::OnLeftMouseClick);
	PlayerInputComponent->BindAction("Release",IE_Pressed, this, &AmainCharacter::OnRightMouseClick);

	
	
}

void AmainCharacter::Jump()
{
	
	Super::Jump();

	
	
}

void AmainCharacter::StopJumping()
{
	Super::StopJumping();

	//AnimInstanceRef->isJumping = false;

}

void AmainCharacter::CarryObjet()
{

	
}

void AmainCharacter::onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

	

	//Refrence and check if this is a box
	if (OtherActor != nullptr)
	{

		//Crate
		MoveableActor  = Cast<AMoveableActor>(OtherActor);

		if (MoveableActor != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black,TEXT("Yal"));
			MoveableActor->print();

			FTransform SocketLocation =  SkeletalMeshComponentRef->GetSocketTransform(TEXT("CarrySocket"));
			OtherActor->AttachToComponent(SkeletalMeshComponentRef,FAttachmentTransformRules::SnapToTargetIncludingScale,TEXT("CarrySocket"));
			//OtherActor->SetActorRelativeTransform(SocketLocation);
			OtherActor->SetActorTransform(SocketLocation);
		}

		ACashDesk* Desk = Cast<ACashDesk>(OtherActor);
		if (Desk && Desk->Camera)
		{
			//FVector Location = Desk->Camera->GetComponentLocation();
			//FRotator Rotation = Desk->Camera->GetComponentRotation();;

		//	CameraComponent->SetWorldLocation(Location);
			//CameraComponent->SetWorldRotation(Rotation);

		//	GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(Desk,1.0f);
			

			
		}
		
	}

	
	

}

void AmainCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AmainCharacter::OpenFridgeDoor(FHitResult OutHit, AFridge* FridgeRef, FName DoorTag)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan,Door->GetName());
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan,Fridge->getcc);

		
		//Check which door to open by Tags
		if (DoorTag == "1")
		{
			//Check if Close/Open
			if (FridgeRef->SceneComponent1->GetRelativeRotation().Yaw == 180.0f)
			{
				FridgeRef->SceneComponent1->SetRelativeRotation(FRotator(0.0f,-90.f,0.0));

			}
			else
			{
				FridgeRef->SceneComponent1->SetRelativeRotation(FRotator(0.0f,180.0f,0.0));

			}

		}else if (DoorTag == "2")
		{
			//Check if Close/Open
			if (FridgeRef->SceneComponent2->GetRelativeRotation().Yaw == 0.0f)
			{
				FridgeRef->SceneComponent2->SetRelativeRotation(FRotator(0.0f,-90.f,0.0));

			}
			else
			{
				FridgeRef->SceneComponent2->SetRelativeRotation(FRotator(0.0f,0.0f,0.0));

			}
		}
		else if (DoorTag == "3")
		{
			//Check if Close/Open
			if (FridgeRef->SceneComponent3->GetRelativeRotation().Yaw == 0.0f)
			{
				FridgeRef->SceneComponent3->SetRelativeRotation(FRotator(0.0f,-90.f,0.0));

			}
			else
			{
				FridgeRef->SceneComponent3->SetRelativeRotation(FRotator(0.0f,0.0f,0.0));

			}
		}	
		
}

void AmainCharacter::StoreProductFridge(const FHitResult& InHitObject, AFridge* FridgeRef)
{
	//Detection Box
		
	if (Cast<UBoxComponent>(InHitObject.Component))
	{
		//UBoxComponent* detectedBox = Cast<UBoxComponent>(OutHit.Component);

		if (bIsGrabbing && FridgeRef)
		{
			GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, InHitObject.Component->GetAttachParent()->GetName());

			if (Product)
			{
				UStaticMeshComponent* DesignedObject = Cast<UStaticMeshComponent>(InHitObject.Component->GetAttachParent());
				if (DesignedObject)
				{
					if (InHitObject.Component->ComponentHasTag("0"))
					{
						FridgeRef->SetFloorStorageLocation(Product,FridgeRef->ProductStorageLocation,FridgeRef->Floor1);
						
					}

					else if (InHitObject.Component->ComponentHasTag("1"))
					{
						FridgeRef->SetFloorStorageLocation(Product,FridgeRef->ProductStorageLocation2,FridgeRef->Floor2);

						
					}

					else if (InHitObject.Component->ComponentHasTag("2"))
					{
						FridgeRef->SetFloorStorageLocation(Product,FridgeRef->ProductStorageLocation3,FridgeRef->Floor3);
						
					}

						
				}
					
				//FridgeRef->PutProductOnFridge(Product,FridgeRef->Floor1);
				//GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, "Valid2");
				//Product->ProductPackAssigned->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
				//Product->ProductPackAssigned->SetWorldLocation(FridgeRef->Floor1->GetSocketLocation("0"));
				//Product->ProductPackAssigned->SetWorldRotation(FRotator(0.0f,180.0f,0.0f));
				//FridgeRef->ProductStorageLocation["0"] = true;
				//Product->ProductPackAssigned->SetSimulatePhysics(false);
				//Product->ProductPackAssigned->WakeRigidBody();
			}
				
		}
			
	}
}

void AmainCharacter::GrabProduct(const FHitResult& InHitObject)
{
	//CARRY BOX
	if (Cast<AProduct>(InHitObject.GetActor()))
	{
		Product = Cast<AProduct>(InHitObject.GetActor());

		if (Product->bIsPlaced)
		{
			//SPAWN ACTOR ON TABLE
		}
		GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, TEXT("Block"));
		GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, InHitObject.GetActor()->GetName());
		Product->BoxCollision->WakeRigidBody();
		Product->BoxCollision->SetSimulatePhysics(false);
		Product->BoxCollision->WakeRigidBody();
		//	Product->bIsPlaced = false;
		bIsGrabbing = true;
		GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("TOGGLE"));

		PhysicHandler->GrabComponentAtLocationWithRotation(InHitObject.GetComponent(),TEXT("CarrySocket"),InHitObject.GetComponent()->GetComponentLocation(),FRotator(0,0,0));

		//GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, PhysicHandler->GetGrabbedComponent()->GetName());


		//PhysicHandler->bRotationConstrained = true;
			
			
			
	}
}

void AmainCharacter::ReleaseProduct()
{

	if (bIsGrabbing && !bIsClearingGoods)
	{
		GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Black, TEXT("HOLDING NOT"));
		bIsGrabbing = false;
		PhysicHandler->ReleaseComponent();
		if (Product && Product->ActorHasTag("ItemProduct"))
		{
			Product->PickedItem->AttachToComponent(Product->BoxCollision,FAttachmentTransformRules::KeepWorldTransform);
			Product->BoxCollision->AttachToComponent(Product->SceneComponent,FAttachmentTransformRules::KeepWorldTransform);
			//Product->CardBoxSkeletalMesh->AttachToComponent(Product->BoxCollision,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Product->BoxCollision->SetSimulatePhysics(true);
			
			//Product->CardBoxSkeletalMesh->Play(false);
			//Product->CardBoxSkeletalMesh->PlayAnimation(Product->OpenBox,false);
		}
		if (Product)
		{
			Product->BoxCollision->AttachToComponent(Product->SceneComponent,FAttachmentTransformRules::KeepWorldTransform);
			Product->CardBoxSkeletalMesh->AttachToComponent(Product->BoxCollision,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Product->BoxCollision->SetSimulatePhysics(true);
			
			//Product->CardBoxSkeletalMesh->Play(false);
			//Product->CardBoxSkeletalMesh->PlayAnimation(Product->OpenBox,false);
		}
		if (CardboardBox)
		{
			CardboardBox->Object->SetSimulatePhysics(true);
		}
		//	Product->AssignedProduct->AttachToComponent(Product->Surrounding,FAttachmentTransformRules::SnapToTargetNotIncludingScale);


		return;
	}
}


