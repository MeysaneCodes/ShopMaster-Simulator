// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "mainCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Regale.generated.h"

UCLASS()
class LEARNING_API ARegale : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARegale();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Regale;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Floor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Floor2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Floor3;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Floor4;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Product Detection")
	UBoxComponent* ProductBox1 ;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Product Detection")
	UBoxComponent* ProductBox2 ;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Product Detection")
	UBoxComponent* ProductBox3 ;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Product Detection4")
	UBoxComponent* ProductBox4;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Product Detection")
	TSubclassOf<AProduct> ProductFilter;

	void PutOnProductOnRegal(TArray<AActor*> OutOverlappedActor, UStaticMeshComponent* Regal);


	//First Regal
	UFUNCTION()
	void OnRegalOneBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnRegalEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//SecondOne
	UFUNCTION()
	void OnRegalBeginOverlap2(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnRegalEndOverlap2(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnRegalBeginOverlap3(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnRegalEndOverlap3(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable)
	void OnRegalBeginOverlap4(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void OnRegalEndOverlap4(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	bool bIsOverlapping1 = false;
	bool bIsOverlapping2 = false;
	bool bIsOverlapping3 = false;
	bool bIsOverlapping4 = false;

	TMap<FName,bool> ProductStorageLocation;
	TMap<FName,bool> ProductStorageLocation2;
	TMap<FName,bool> ProductStorageLocation3;
	TMap<FName,bool> ProductStorageLocation4;

	AmainCharacter* Character;
	bool bIsSearchingForProductRunning = false;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
