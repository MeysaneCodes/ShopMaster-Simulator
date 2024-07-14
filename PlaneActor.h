// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "PlaneActor.generated.h"

UCLASS()

class LEARNING_API APlaneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaneActor();
	UPROPERTY(EditAnywhere, Category = "First Value")
	float CurrentNumber = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Main Components")
	UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Main Mesh")
	UStaticMeshComponent* MovingCube;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Timeline")
	UTimelineComponent* timeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline")
	UCurveFloat* floatCurve;

	UFUNCTION(BlueprintCallable)
	void TimelineUpdate(float Value);

	UFUNCTION(BlueprintCallable)
	void FinishEvent() ;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
