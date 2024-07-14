// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "mainCharacter.h"
#include "US_ComputerScreenWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CashDesk.generated.h"

UCLASS()
class LEARNING_API ACashDesk : public AActor
{
	GENERATED_BODY()

private:
	UUS_ComputerScreenWidget* ScreenWidget;

	
public:	
	// Sets default values for this actor's properties
	ACashDesk();

protected:

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Scene")
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Direction")
	UArrowComponent* DirectionArrow;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Cash Desk")
	UStaticMeshComponent* CashDesk;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Cash Desk")
	UStaticMeshComponent* Computer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Cash Desk")
	UWidgetComponent* ScreenComputer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Cash Desk")
	UStaticMeshComponent* ConveyorBelt;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Cash Desk")
	UBoxComponent* OverlappingBox;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Cash Desk")
	UBoxComponent* StopSensor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Cash Desk")
	UBoxComponent* ScannerDetector;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product Refrence")
	TSubclassOf<AProduct> ProductClassRef;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Slot Collision")
	UBoxComponent* Slot1CollisionBox1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Slot Collision")
	UBoxComponent* Slot1CollisionBox2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Slot Collision")
	UBoxComponent* Slot1CollisionBox3;

	//UFUNCTIONS
	UFUNCTION()
	void AddtoScannedProducts();
	//Overlaps
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	//Variables
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Scanner Add")
	//bool IsAdded = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Cash Desk")
	float Speed = 50.0f;

	bool shouldMove = false;
	TMap<FName,bool> ConditionList;
	
	void ConveyorBeltDetector(float inSpeed);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AmainCharacter* mainCh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	UCameraComponent* Camera;

};
