// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include <Engine/Classes/Components/StaticMeshComponent.h>
#include "Interactable.h"
#include "Snake.h"


// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
	// Таймеры на увеличение блока
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &ABlock::GetScale, 90.f, false); //60

	FTimerHandle Handle2;
	GetWorld()->GetTimerManager().SetTimer(Handle2, this, &ABlock::GetScale2, 200.f, false); //120
	
	FTimerHandle Handle3;
	GetWorld()->GetTimerManager().SetTimer(Handle3, this, &ABlock::GetScale3, 310.f, false); //180
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlock::Interact(AActor* Interactor, bool bIsHead)
{
	
	if (bIsHead)
	{

		auto Snake = Cast<ASnake>(Interactor);
		if (IsValid(Snake))
		{
			Snake->Destroy();
			//Snake->Life--;
		}
	}	
}

void ABlock::GetScale()
{
	this->SetActorScale3D(FVector(1.6, 1.6, 0.0));	
}

void ABlock::GetScale2()
{
	this->SetActorScale3D(FVector(2.0, 2.0, 0.0));
}

void ABlock::GetScale3()
{
	this->SetActorLocation(FVector(60.0, 18.0, 0.0));
	this->SetActorScale3D(FVector(2.75, 4.75, 0.0));
}






	



















