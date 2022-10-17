// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SNAKEGAME_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// UFUNCTION() нужно убрать,чтобы не было даже намека,что этот интерфейс будет просачиватьс€ в BP
	// ƒобавл€ем булевую переменную 
		virtual void Interact(AActor* Interactor,bool bIsHead ); //// добав€лем bIsHead в файл

};
