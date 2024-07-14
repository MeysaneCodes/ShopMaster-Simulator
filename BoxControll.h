// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BoxControll.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API UBoxControll : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	bool bIsOpen;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Product")
	bool bIsClose;
	
	
};
