// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "US_PriceWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API UUS_PriceWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Settings")
	FString Price = "";
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Settings")
	FString ProductName = "";

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	
};
