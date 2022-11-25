// Fill out your copyright notice in the Description page of Project Settings.


#include "BFood.h"
#include "Snake.h" //����������� header`� ������ ��� �������� �������


// Sets default values
ABFood::ABFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABFood::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		// ���� ��������� � ������.
		auto Snake = Cast<ASnake>(Interactor);
		// ����� �������� ���������� ��������� �� ���������� 
		if (IsValid(Snake))
		{
			// �������� �  Food ����� ������ ��������.
			// �� ��� ���������� AddSnakeElement 
			// () - �� ��������� ����������� 1 �������.
			Snake->AddSnakeElement();
			Snake->Score += Bonus;
			Snake->Score++;
			Snake->newScore = Snake->Score;

			// ��������� ����������� ��� ������ ���?
			// if(Snake->Score > 10)
			// {
			//	 this =  GetWorld()->SpawnActor(....
			// }

			// ����������� ��� ����� overlap
			this->Destroy();
		}
	}
}

