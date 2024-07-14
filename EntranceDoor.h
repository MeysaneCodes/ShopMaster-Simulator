// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "EntranceDoor.generated.h"

UCLASS()
class LEARNING_API AEntranceDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntranceDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* RDoorWall;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* LDoorWall;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* RightFrame;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* RightGlass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* RightDoorHandler;
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* LeftFrame;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* LeftGlass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* LeftDoorHandler;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPhysicsConstraintComponent* RightPhysicsConstraint;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPhysicsConstraintComponent* LeftPhysicsConstraint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
