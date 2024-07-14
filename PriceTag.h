// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "PriceTag.generated.h"

UCLASS(Blueprintable)
class LEARNING_API APriceTag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APriceTag();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Scene")
	USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Properties")
	UStaticMeshComponent* PriceTag;
	



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Properties")
	UWidgetComponent* PriceWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product Information")
	FString Price = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product Information")
	FString ProductName = "";

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Product Information")
	TArray<FString> Currencies = {TEXT("€"),TEXT("$")};

};
