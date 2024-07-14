// Fill out your copyright notice in the Description page of Project Settings.


#include "PriceTag.h"

#include "US_PriceWidget.h"


// Sets default values
APriceTag::APriceTag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

		
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;
	PriceTag = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Price Tag"));
	PriceTag->SetupAttachment(SceneComponent);
	PriceWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Price Tag Widget"));
	PriceWidget->SetupAttachment(PriceTag);
	

}

// Called when the game starts or when spawned
void APriceTag::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void APriceTag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UUS_PriceWidget* Widget = Cast<UUS_PriceWidget>(PriceWidget->GetUserWidgetObject()))
	{
		Widget->ProductName = ProductName;
		Widget->Price = Price + Currencies[0];
	}
}

