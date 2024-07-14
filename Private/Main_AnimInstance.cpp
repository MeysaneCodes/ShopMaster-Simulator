// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_AnimInstance.h"


UMain_AnimInstance::UMain_AnimInstance()
{
	isRunning = false;
	isTurning = false;
	isJumping = false;
	testString = "Hallo";
}

void UMain_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Now"));

}



