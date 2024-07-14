// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardboardBox.generated.h"

UCLASS()
class LEARNING_API ACardboardBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardboardBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Scene")
	USceneComponent* SceneComponent;
	
	

	

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Settings")
	FString Tag;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Settings")
	UStaticMesh* CardBox;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Settings")
	UStaticMesh* ProductPack;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	USkeletalMeshComponent* CardBoxSkeletalMesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Settings")
	UStaticMeshComponent* Object;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Move Trigger")
	bool bIsCardPlaced = false;

	
};
