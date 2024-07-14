// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "US_ComputerScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API UUS_ComputerScreenWidget : public UUserWidget
{
	GENERATED_BODY()

	

private:

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item Properties")
	UListView* ItemsListIn;

	UFUNCTION(BlueprintCallable)
	void getItemsScanned();
	

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item Properties")
	FText ItemPurchased;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item Properties")
	FText ItemsAmount;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item Properties")
	FText ItemPrice;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item Properties")
	UListView* ItemsScanned;
	virtual void NativePreConstruct() override;
	
};
