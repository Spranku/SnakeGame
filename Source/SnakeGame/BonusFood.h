// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "BonusFood.generated.h"

/**
 * 
 */


UCLASS()
class SNAKEGAME_API ABonusFood : public AFood //Мн.наследование
{
	GENERATED_BODY()
public:
	/////UPROPERTY(BlueprintReadWrite)
	/////	ABonusFood* FoodBonusClass;
protected:
	virtual void BeginPlay() override;
public: 
	
	virtual void Interact(AActor* Interactor, bool bIsHead) override;
	int Bonus = 50;
	void SetLocation();
	void SetLocation2();
	void SetLocation3();
};
