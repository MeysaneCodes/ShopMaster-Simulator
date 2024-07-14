// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PriceTag.h"
#include "Product.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Fridge.generated.h"

class AmainCharacter;

UCLASS()
class LEARNING_API AFridge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFridge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Fridge;

	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* DoorFridge1;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* DoorFridge2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* DoorFridge3;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DoorHandle")
	UBoxComponent* DoorOpener1 ;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DoorHandle")
	UBoxComponent* DoorOpener2 ;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DoorHandle")
	UBoxComponent* DoorOpener3 ;

	//Product Overlap box
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Product Detection")
	UBoxComponent* ProductBox1 ;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Product Detection")
	UBoxComponent* ProductBox2 ;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Product Detection")
	UBoxComponent* ProductBox3 ;
	
	FOnTimelineFloat TrackCurve;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Timeline")
	UCurveFloat* CurveFloat;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Timeline")
	UTimelineComponent* TimelineComponent;

	UFUNCTION()
	void UpdateDoorRotation(float value);

	UFUNCTION()
	void onComponentHitFirst(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void onComponentHitSecond(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void onComponentHitThird(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnBoxOneBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	

private:

	AmainCharacter* Character;
	bool bIsSearchingForProductRunning = false;

	

	TArray<AActor*> OverlappedActors;
	TArray<AActor*> OverlappedActors2;
	TArray<AActor*> OverlappedActors3;

	int RunAmount = 0;
	bool bIsRunning = false;

	void AddPriceToProduct(UStaticMeshComponent* &ProductPack,AProduct* &InCarriedProduct, TMap<UStaticMeshComponent*,APriceTag*> &PricePerProduct,TArray<UStaticMeshComponent*> &ProductFloor,FString const& IDKey, const UStaticMeshComponent*  InPutFloor,TMap<FName,bool>& InProductStorage);




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//virtual void On(FKey ButtonClicked) override;
	void OpenDoor();
	void CloseDoor();


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* SceneComponent1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* SceneComponent2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* SceneComponent3;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Floor1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Floor2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Floor3;
	
	void Delay();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Properties")
	TMap<FName,bool> ProductStorageLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Properties")
	TMap<FName,bool> ProductStorageLocation2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Properties")
	TMap<FName,bool> ProductStorageLocation3;

	 void SetFloorStorageLocation(AProduct* CarriedProduct,TMap<FName,bool>& ProductStorage, UStaticMeshComponent* PutInFloor);
	int c = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Properties")
	TSubclassOf<APriceTag>  PriceTagRefrence;

	TArray<UStaticMeshComponent*> ProductFloor1,ProductFloor2,ProductFloor3;
	TArray<FName> Sockets,Sockets2,Sockets3;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Properties")
	TMap<UStaticMeshComponent*,APriceTag*> PricePerProduct1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Properties")
	TMap<UStaticMeshComponent*,APriceTag*> PricePerProduct2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Properties")
	TMap<UStaticMeshComponent*,APriceTag*> PricePerProduct3;

	int ConvertStringToInt(const FString& str);

};
