// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Main_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API UMain_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UMain_AnimInstance();

protected:

	

public:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;



	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Settings")
	bool isRunning;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Settings")
	bool isJumping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Settings")
	bool isTurning;

	FString testString = "Hi There!";
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
	UAnimSequence* IdleeAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
	UAnimSequence* RunningAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
	UAnimSequence* JumpingAnimation;
	
	
	

private:
	
};
