// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Product.generated.h"

UCLASS(Blueprintable)
class LEARNING_API AProduct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProduct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	

	

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	FString Tag;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Scene")
	USceneComponent* SceneComponent;

	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Scene")
	//USceneComponent* Surrounding;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Collision")
	UBoxComponent* BoxCollision;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	UStaticMeshComponent* ProductPackAssigned;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	UStaticMeshComponent* ProductPackAssigned2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	UStaticMeshComponent* ProductPackAssigned3;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	UStaticMeshComponent* ProductPackAssigned4;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	UStaticMeshComponent* PickedItem;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	TArray<UStaticMesh*> ProductsList;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	USkeletalMeshComponent* CardBoxSkeletalMesh;

	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	//UStaticMesh* ProductPack;

	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Move Trigger")
	//bool bIsPlaced = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	UAnimationAsset* OpenBox;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	UAnimationAsset* CloseBox;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Properties")
	int ProductAmount = 1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product Information")
	TMap<FString,FString> ProductDetails;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product Information")
	FString Price = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product Information")
	FString ProductName = "";

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Product Information")
	TArray<FString> Currencies = {TEXT("€"),TEXT("$")};

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Product Information")
	bool bIsPlaced = false;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Product Settings")
	UStaticMesh* itemDefault;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Properties")
	bool bIsScanned = false;
};
