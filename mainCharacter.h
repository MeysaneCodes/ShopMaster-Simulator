// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardboardBox.h"
#include "Main_AnimInstance.h"
#include "MoveableActor.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Fridge.h"
#include "Product.h"
#include "Components/WidgetInteractionComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "mainCharacter.generated.h"

class USpringArmComponent;

UCLASS()
class LEARNING_API AmainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AmainCharacter();
	
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Camera")
	//USpringArmComponent* SpringArmComponent;
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Camera")
	//UCameraComponent* CameraComponent;

	

	void MoveForward(float AxisValue);
	void MoveBackward(float AxisValue);

	
	void MoveRight(float AxisValue);
	void TimerCallBack();
	void TurnAround();
	void CallJump();
	void ToggleCarry();
	void OnRightMouseClick();
	void OnLeftMouseClick();

	AFridge* TestFridg;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Properties")
	USkeletalMeshComponent* SkeletalMeshComponentRef;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Overlaps")
	UBoxComponent* OverlapBox;

	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Box")
	//UBoxComponent* CrateBox;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Properties")
	UAnimMontage* CarryAnimation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Properties")
	UAnimMontage* GrabAnimation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Properties")
	AMoveableActor*  MoveableActor;

	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Properties")
	TSubclassOf<UGameInstance>  AnimationClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Slot")
	UBoxComponent* ProductSlot;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Widget")
	UWidgetInteractionComponent* InteractionWidget;

	//Default Variables
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Animation Settings")
	float BlendOutTime_CarryAnimation = 0.8f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Range")
	float GrabRange = 1500.0f;

	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Properties")
	UPhysicsHandleComponent* PhysicHandler;


	bool bIsGrabbing = false;
	bool bIsClearingGoods = false;

	void ReleaseProduct();

private:
	UMain_AnimInstance* AnimInstanceRef;
	APlayerController* PlayerController;
	bool isCarrying;
	AProduct* Product;
	ACardboardBox* CardboardBox;

	virtual void Jump() override;
	virtual void StopJumping() override;

	void CarryObjet();
	UFUNCTION()
	void onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	void OpenFridgeDoor(FHitResult OutHit, AFridge* FridgeRef, FName DoorTag);
	void StoreProductFridge(const FHitResult& InHitObject,AFridge* FridgeRef);
	void GrabProduct(const FHitResult& InHitObject);
	
};
