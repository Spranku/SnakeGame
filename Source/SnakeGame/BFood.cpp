// Fill out your copyright notice in the Description page of Project Settings.


#include "BFood.h"
#include "Snake.h" //Подключение header`а змейки для проверки события


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
		// Каст интеракта к змейке.
		auto Snake = Cast<ASnake>(Interactor);
		// После проверим полученный указатель на валидность 
		if (IsValid(Snake))
		{
			// Пропишем в  Food вызов одного эдемента.
			// Мы уже определили AddSnakeElement 
			// () - по умолчанию добавляется 1 элемент.
			Snake->AddSnakeElement();
			Snake->Score += Bonus;
			Snake->Score++;
			Snake->newScore = Snake->Score;

			// Возможная конструкция для спавна еды?
			// if(Snake->Score > 10)
			// {
			//	 this =  GetWorld()->SpawnActor(....
			// }

			// Уничтожение еды после overlap
			this->Destroy();
		}
	}
}

