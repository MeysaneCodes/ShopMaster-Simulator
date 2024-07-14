// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MoveableActor.generated.h"

UCLASS()
class LEARNING_API AMoveableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UStaticMeshComponent* Crate;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void print();
};
